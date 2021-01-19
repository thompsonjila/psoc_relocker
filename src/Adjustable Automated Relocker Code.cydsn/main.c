/* ================================================================
Automated Laser Frequency Relocking Procedure
Original Programmer: Denton Wu
Last modified: Sept 2018
Notes:

Greetings relocker user or improver. This is the main relocker algorithm.
There are two parts to the code: the setup and the relocking procedure. 

If float voltages will not display, PSoC Creator has updated and you need
to reset the gcc compiler options to handle floats (see manual).
==================================================================*/

#include "project.h"
#include "utility.h"
#include <stdbool.h>
#include <stdio.h>


int main(void) {
  CyGlobalIntEnable                // enable global interrupts...
  int MAX_FAILS_BEFORE_LED = 20;   // consecutive relock attempts before red LED turns on
  int SWEEP_DELAY_US = 1;          // software delay in microseconds/step to slow sweep
  bool TEST_VOLTAGE_MODE = false;  // loop an input/output voltage test sequence
  
  int16 logErrMon[255] = {};     // Do not change without taking care of overflow in code below!
                                 // Should be upperDACSweepLevel-lowerDACSweepLevel (4673 for 0.5V sweep)
                                 // but this takes too long to send over serial so we will store 512 last pts
  bool boolLogErrMon = true;     // 
  int16 logErrMonCounter = 0;    // current array index
    
  char8 serialBuffer[255];       // allocate space for serial messages
  int32 lockedLFLevel;           // stores calibrated in-lock LF voltage
  int32 upperLockedLFLevel = 0;  // in-lock LF voltage plus 150mV
  int32 lowerLockedLFLevel = 0;  // in-lock LF voltage minus 150mV
  int32 upperDACSweepLevel = 0;  // DAC sweep upper level
  int32 lowerDACSweepLevel = 0;  // DAC sweep lower level
  float lockedLFV, aboveLFV = 0, belowLFV = 0;
  int32 LFOutputMeas;            // stores a LF voltage measurement during sweep
  int16 errMonMaximum = 0;       // stores unlocked error monitor's maximum voltage
  int16 errMonMinimum;           // stores unlocked error monitor's minimum voltage
  int16 errMonThreshold;         // stores unlocked error monitor's threshold at half the maximum
  int16 errMonThreshold1;         // stores unlocked error monitor's threshold at half the maximum
  int16 errMonThreshold2;         // stores unlocked error monitor's threshold at half the maximum
  int16 errMonMeasurement;       // stores last error monitor voltage measurement
  int lockFails = 0;             // number of consecutive relock failures
  int32 counterLED = 0;          // number of consecutive relock failures
  int blinkLED = 0;              // boolean for blinking diagnostic LEDs
  int LFRange;         // LF range should be 8, 22, or 28 (volts) depending on loop filter model
  int DAC150mVLevel;   // corresponds to 150mV when 2^16 is (LFRange [Volts])
  int DACOffset; // converts 2^15 DAC counts to 0V actual output (calibrating the op amp circuits)
  float DACRange; // calibrating the full voltage output would give slightly better DAC conversion

  //tempTrigger_Write(0); // temporary
  
  bool debugJustCalibrated = false;
  bool debugFirstLFSample = true;
  bool debugFirstErrMonSample = true;
  bool debugDropDetected = false;
  
  switches_Write(0); // writes to all pins attached to 'switches': aPin, bPin; box is inactive
  greenLight_Write(1); CyDelay(50);   // LED test
  yellowLight_Write(1); CyDelay(50); 
  redLight_Write(1); CyDelay(50); 
  orangeLight_Write(1); CyDelay(50);
  greenLight_Write(0); CyDelay(50);
  yellowLight_Write(0); CyDelay(50);
  redLight_Write(0); CyDelay(50);
  orangeLight_Write(0); CyDelay(50);
  CyDelay(100);
  greenLight_Write(1); yellowLight_Write(1); orangeLight_Write(1); redLight_Write(1);
  
  CyDelay(100);
  greenLight_Write(0); yellowLight_Write(0); orangeLight_Write(0); redLight_Write(0);

  errMonADC_Start();        // power on ADC
  errMonADC_StartConvert(); // begin monitoring error signal monitor ADC
  LFOutADC_Start();         // begin monitoring LF output ADC
  LFOutADC_StartConvert();  // begin monitoring error signal monitor ADC
  coarseDAC_Start();
  fineDAC_Start();
  
  SW_Tx_UART_1_Start();     // begin USB Serial communications  
  Serial("SKYNET: Triggered Relocker v1.0. I am awake!");
  sprintf(serialBuffer, "Compiled at %s on %s.", __TIME__, __DATE__); 
  Serial(serialBuffer);
  
//  while(1) {
//    int16 testint[512] = {};
//    testint[1] = 100;
//    testint[3] = 5050;
//    SendDataArray(logErrMon, sizeof(logErrMon) / sizeof(logErrMon[0]), logErrMonCounter);
//  }
  
  // Check LF range setting and appropriately sets input/output voltage calibration scales
  setupFreeSoc(TEST_VOLTAGE_MODE, &LFRange, &DAC150mVLevel, &DACOffset, &DACRange);
  
  // Loop until user sets switch to "Calibrate". Make sure you have set the LF Range first!
  if (calibratePin_Read() == 0) {
    Serial("Awaiting calibration. Set Switch 4 to 'Choose'.");
    while (calibratePin_Read() == 0) {
      CyDelay(250);
      blinkLED = 1 - blinkLED;
      yellowLight_Write(blinkLED);
    }
  }

  Serial("Beginning main sequence (calibrating, then attempting to relock).");
  Serial("Switch to Lock to engage relocker or sample the error signal range.");
  for(;;) {
    errMonMinimum = 0;     // initialize these to ridiculous values
    errMonMaximum = 32767;
    
    while(calibratePin_Read() == 1) {
      // Enter calibration procedure (set or reset LF average and/or error monitor maximum)
      greenLight_Write(0);
      yellowLight_Write(1);

      if(sampleErrorMonitor_Read() == 1) { // send message so it is clear what we are sampling.
        if (debugFirstErrMonSample) {
          Serial("Now sampling out-of-lock maximum error signal voltage.");
          debugFirstErrMonSample = false; 
          debugFirstLFSample = true;
        }
        while(sampleErrorMonitor_Read() == 1) {
          (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT); // docs say: always check
          errMonMeasurement = errMonADC_GetResult16();
          if (errMonMeasurement < errMonMaximum) { // found new maximum voltage (op amp inverted)
            errMonMaximum = errMonMeasurement;
          } else if (errMonMeasurement > errMonMinimum) {
            errMonMinimum = errMonMeasurement;
          }
        }
        
        /* here are the initial thresholds */
        // changing /4 to /6... etc.
        errMonThreshold = (3*errMonMaximum + errMonMinimum)/4; // for slope: thresh above avg
        errMonThreshold1 = errMonThreshold; // for slope: thresh above avg
        errMonThreshold2 = (errMonMaximum + 3*errMonMinimum)/4; // other slope: thresh below avg
        
        errMonThreshold = errMonMaximum + (( errMonMinimum - errMonMaximum ) / 3); // for slope: thresh above avg
        errMonThreshold1 = errMonThreshold; // for slope: thresh above avg
        errMonThreshold2 = errMonMinimum - ((errMonMinimum - errMonMaximum ) / 3); // other slope: thresh below avg
        /* here we are assuming a symmetric error signal. we are assuming a rising slope for the central error signal */
        
      } else {
        if (debugFirstLFSample) { // send message so it is clear we are calibrating.
          Serial("Sampling average in-lock LF output.");
          debugFirstErrMonSample = true;
          debugFirstLFSample = false; 
        }
        // Now measure in-lock loop filter output voltage. Take the last measurement, no averaging
        (void)LFOutADC_IsEndConversion(LFOutADC_WAIT_FOR_RESULT);
        lockedLFLevel = LFOutADC_GetResult32(); // Measure LF out voltage.
        
        lockedLFV = LFOutADC_CountsTo_Volts(lockedLFLevel);
        // Set bounds 200mV above/below the in-lock output voltage.
        // test: 300 mV?
        aboveLFV = lockedLFV + 0.150;
        belowLFV = lockedLFV - 0.150;
        // upperLockedLFLevel = lockedLFLevel + DAC150mVLevel;
        // lowerLockedLFLevel = lockedLFLevel - DAC150mVLevel;
        upperLockedLFLevel = LFOutADC_VoltsTo_Counts(aboveLFV);
        lowerLockedLFLevel = LFOutADC_VoltsTo_Counts(belowLFV);
        upperDACSweepLevel = DAC_VoltsTo_Counts(aboveLFV, DACRange, DACOffset);
        lowerDACSweepLevel = DAC_VoltsTo_Counts(belowLFV, DACRange, DACOffset);
      }
      
      debugJustCalibrated = true;
    }
    
    if (debugJustCalibrated) { // diagnostics
      float V1 = errMonADC_CountsTo_Volts(errMonMinimum);
      float V2 = errMonADC_CountsTo_Volts(errMonMaximum);
      float V3 = errMonADC_CountsTo_Volts(errMonThreshold1);
      float V4 = errMonADC_CountsTo_Volts(errMonThreshold2);
       Serial("Calibration complete.");
      sprintf(serialBuffer, "--> LF avg: %.3fV, sets bounds at [%ld, %ld]=[%.3fV, %.3fV]",
        lockedLFV, lowerLockedLFLevel, upperLockedLFLevel, belowLFV, aboveLFV); 
      Serial(serialBuffer);
      sprintf(serialBuffer, "--> DAC sweep range: [%ld, %ld]=[lownum, highnum]=[%.3fV, %.3fV]",
        upperDACSweepLevel, lowerDACSweepLevel, aboveLFV, belowLFV); 
      Serial(serialBuffer);
      sprintf(serialBuffer, "--> Err monitor: [%d, %d]=[%.3fV, %.3fV]; threshold %.3f %.3f",
        errMonMinimum, errMonMaximum, V1, V2, V3, V4); 
      Serial(serialBuffer);
      debugJustCalibrated = false;
      debugFirstLFSample = true;
    }

    // Relocker is now watching for a drop!
    greenLight_Write(1);
    yellowLight_Write(0);
    (void)LFOutADC_IsEndConversion(LFOutADC_WAIT_FOR_RESULT);
    LFOutputMeas = LFOutADC_GetResult32(); // Measure LF output, check if it is unlocked
    
    if ((LFOutputMeas < upperLockedLFLevel) || (LFOutputMeas > lowerLockedLFLevel)) {
      if(blockLockPin_Read() == 1) { // loop here until blockLock TTL is low
   //     sprintf(serialBuffer, "Detected dropped lock (%.3fV). Waiting for Block Lock TTL low before relocking...",
    //      LFOutADC_CountsTo_Volts(LFOutputMeas)); 
   //       Serial(serialBuffer);
        while(blockLockPin_Read() == 1) {
          if(counterLED >= 300000) { // nice counter trick to make about 2Hz blinking
            counterLED = 0;
            orangeLight_Write(blinkLED = 1 - blinkLED);
          }
          counterLED++;
        }
      } else {
   //     sprintf(serialBuffer, "Detected dropped lock (%.3fV). Block Lock TTL is low so I'm relocking now.",
   //       LFOutADC_CountsTo_Volts(LFOutputMeas)); 
  //      Serial(serialBuffer);
      }
      
      greenLight_Write(0);
      orangeLight_Write(1);
      lockFails = 0;       // count sweep fails
      debugDropDetected = true;
    }
    
    
    while ((LFOutputMeas < upperLockedLFLevel) || (LFOutputMeas > lowerLockedLFLevel)) {
      switches_Write(1);   // control loop filter with microprocessor
      //tempTrigger_Write(0); // temporary
      bool sweptPastThresh = false;     // error monitor has crossed threshold once
      bool errorMonitorInRange = false; // error monitor has crossed back into range
      int32 sweepV = upperDACSweepLevel;
      logErrMonCounter = 0;
      
      coarseDAC_SetValue((0xff00 & sweepV) >> 8); // set coarseDAC sweep voltage
      fineDAC_SetValue(0x00ff & sweepV);          // add in fineDAC voltage with circuitry
      
      while(!errorMonitorInRange) {
        coarseDAC_SetValue((0xff00 & sweepV) >> 8); // set coarseDAC sweep voltage
        fineDAC_SetValue(0x00ff & sweepV);          // add in fineDAC voltage with circuitry
        
      //  CyDelay(1);
        
        (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT);
        // int16 errorMonitorADC = errMonADC_GetResult16();
        int16 testV1 = errMonADC_GetResult16();
        
        (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT);
        int16 testV2 = errMonADC_GetResult16();
        (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT);
        int16 testV3 = errMonADC_GetResult16();
        (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT);
        int16 testV4 = errMonADC_GetResult16();
        (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT);
        int16 testV5 = errMonADC_GetResult16();
        
        int32 errorMonitorADC = (testV1 + testV2 + testV3 + testV4 + testV5) / 5;
        logErrMon[logErrMonCounter] = errorMonitorADC;
        
       // for current sweep direction, only need to know about threshold 1...
       // if ((errorMonitorADC < errMonThreshold1) || (errorMonitorADC > errMonThreshold2)) {
        if (errorMonitorADC < errMonThreshold1) {
          sweptPastThresh = true; // record if error signal has crossed threshold once
       // } else if (sweptPastThresh && (errorMonitorADC > errMonThreshold1) && (errorMonitorADC < errMonThreshold2)) {
        } else if (sweptPastThresh && (errorMonitorADC > errMonThreshold2)) {
          switches_Write(0); // this is where we actually 'relock'
          sweptPastThresh = false; // record if error signal has crossed threshold once
          // errorMonitorInRange = true; // error signal has entered back into the linear region
          //tempTrigger_Write(1); // temporary
      
       // sweepV=sweepV+100;
      //coarseDAC_SetValue((0xff00 & sweepV) >> 8); // set coarseDAC sweep voltage
      //fineDAC_SetValue(0x00ff & sweepV);          // add in fineDAC voltage with circuitry
       // CyDelayUs(20);  
    
          break; // attempt a relock!
        }
        
        if (sweepV >= lowerDACSweepLevel) { // end of sweep, retry sweep
          
          logErrMonCounter = 0;
          sweepV = upperDACSweepLevel;
          coarseDAC_SetValue((0xff00 & sweepV) >> 8); // set coarseDAC sweep voltage
          fineDAC_SetValue(0x00ff & sweepV);          // add in fineDAC voltage with circuitry
          
          CyDelayUs(10); //Delay ? after each sweep
        
          sweptPastThresh = false;
          lockFails++;
      //  sprintf(serialBuffer, "FAIL."); 
      //  Serial(serialBuffer);
          if (lockFails == MAX_FAILS_BEFORE_LED) {
            redLight_Write(1); // Roxanne, put on the red light
            sprintf(serialBuffer, "Failed to relock %d times (MAX_FAILS_BEFORE_LED).",
              MAX_FAILS_BEFORE_LED); 
            Serial(serialBuffer);
          }
        }
        
       //  CyDelayUs(SWEEP_DELAY_US); // slow down sweep slightly (see plot in manual)
        logErrMonCounter++;
        if (logErrMonCounter > 255) {
          logErrMonCounter = 0;
          sweptPastThresh = false;
        }
        sweepV++; // increase or decrease sweep voltage and try again
        
      }
      
      (void)LFOutADC_IsEndConversion(LFOutADC_WAIT_FOR_RESULT);
      LFOutputMeas = LFOutADC_GetResult32(); // re-measure LF output
      // sprintf(serialBuffer, "Broke free! %ld=%0.3f is in range of [%ld, %ld]?", LFOutputMeas,
      //  LFOutADC_CountsTo_Volts(LFOutputMeas), lowerLockedLFLevel, upperLockedLFLevel); 
      // Serial(serialBuffer);
    }
  
    if (debugDropDetected) {
      // Loop filter has returned to central region; switch back into conventional mode now
      debugDropDetected = false;
      sprintf(serialBuffer, "Relock #%d successful! LF Output at %0.3f V.", lockFails, LFOutADC_CountsTo_Volts(LFOutputMeas));
      Serial(serialBuffer);
      if (boolLogErrMon) {
        SendDataArray(logErrMon, sizeof(logErrMon) / sizeof(logErrMon[0]), logErrMonCounter, errMonThreshold1, errMonThreshold2);
      }
      greenLight_Write(1);
      orangeLight_Write(0);
      redLight_Write(0);
      // tempTrigger_Write(0);
    }
  }
}

/* You got a fast car /
I want a ticket to anywhere /
Maybe we make a deal /
Maybe together we can get somewhere /
Anyplace is better /
Starting from zero got nothing to lose /
Maybe we'll make something /
Me, myself I got nothing to prove */