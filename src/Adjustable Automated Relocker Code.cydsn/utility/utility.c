#include "project.h"
#include "cytypes.h"
#include <stdbool.h>
#include <stdio.h>

// Send a message through serial communication, always ending in a CRLF character termination.
void Serial(const char8 string[]) {
  SW_Tx_UART_1_PutString(string);
  SW_Tx_UART_1_PutCRLF();
}

// Send a message through serial communication, always ending in a CRLF character termination.
void SendDataArray(int16 data[], int arrayLength, int lastSet, int thresh1, int thresh2) {
  char8 serialBuffer[255]; // allocate space for serial message
  sprintf(serialBuffer, "data[%d,%d,%d]:", lastSet, thresh1, thresh2); 
  SW_Tx_UART_1_PutString(serialBuffer);
  for(int ii = 0; ii < arrayLength; ii++) {
    SW_Tx_UART_1_PutHexInt(data[ii]);
  }
  SW_Tx_UART_1_PutCRLF();
}

int32 LFOutADC_VoltsTo_Counts(float volts) {
 return ((int32) (volts * LFOutADC_CountsPerVolt + LFOutADC_Offset));
}
int16 errMonADC_VoltsTo_Counts(float volts) {
 return ((int16) (volts * errMonADC_countsPerVolt + errMonADC_offset));
}
int32 DAC_VoltsTo_Counts(float volts, float DACRange, int DACOffset) {
 return ((int32) (32768 - DACOffset - volts * (65535.0/DACRange)));
}

void setupFreeSoc(bool TEST_VOLTAGE_MODE, int *LFRange, int *DAC150mVLevel, int *DACOffset,
  float *DACRange) {
  char8 serialBuffer[255];       // allocate space for serial messages
  int blinkLED = 1;
  
  errMonADC_SetGain(-3830); // 3832
  errMonADC_SetOffset(2006); // 2038 calibrated 10/19/2018
  while(true) {
    int LFsettings = 0;
    if (setting28V_Read() == 1) { // find selected loop-filter model AND set scales
      *LFRange = 28;
      LFOutADC_SetOffset(28428);
      LFOutADC_SetGain(-1942);
      *DAC150mVLevel = 351;
      *DACOffset = 595;
      *DACRange = 28.2532;
      Serial("Running in '28V Loop Filter' mode.");
      LFsettings++;
    } if (setting22V_Read() == 1) {
      *LFRange = 22;
      LFOutADC_SetOffset(27048);
      LFOutADC_SetGain(-2390);
      *DAC150mVLevel = 447;
      *DACOffset = 1100;
      *DACRange = 20.6672;
      Serial("Running in '22V Loop Filter' mode.");
      LFsettings++;
    } if (setting8V_Read() == 1) {
      *LFRange = 8;
      LFOutADC_SetOffset(27715);
      LFOutADC_SetGain(-6745);
      *DAC150mVLevel = 1229;
      *DACOffset = 780; // 450
      *DACRange = 7.846774; // 7.636774
      Serial("Running in '8V Loop Filter' mode.");
      LFsettings++;
    }
    if (LFsettings == 0) {
      Serial("Loop filter voltage setting could not be found. Is +/-15V on? Restart me.");
      while(1) {
        redLight_Write(blinkLED);
        blinkLED = 1 - blinkLED;
        CyDelay(250);
      }
    } else if (LFsettings > 1) {
      Serial("Error: multiple loop filter voltage settings were measured. Check electronics");
      while(1) {
        redLight_Write(blinkLED);
        blinkLED = 1 - blinkLED;
        CyDelay(250);
      }
    }
    
    
    int32 sweepV = DAC_VoltsTo_Counts(0.5, *DACRange, *DACOffset);
    
    if (!TEST_VOLTAGE_MODE) { // we're not testing? Okay, get back to work
      break;
    }
    
    greenLight_Write(blinkLED); redLight_Write(blinkLED); 
    yellowLight_Write(1-blinkLED); orangeLight_Write(1-blinkLED); 
    blinkLED = 1 - blinkLED;
    
    (void)LFOutADC_IsEndConversion(LFOutADC_WAIT_FOR_RESULT);
    int32 D1 = LFOutADC_GetResult32(); // Measure LF out voltage.
    float V1 = LFOutADC_CountsTo_Volts(D1);
    (void)errMonADC_IsEndConversion(errMonADC_WAIT_FOR_RESULT); // docs say: always check
    int16 D2 = errMonADC_GetResult16();
    float V2 = errMonADC_CountsTo_Volts(D2);
    sprintf(serialBuffer, "Measured LF output: %.3f V (%5ld); error monitor: %.3f V (%5d)",
      V1, D1, V2, D2);
    Serial(serialBuffer);
    
    switches_Write(1); // control loop filter with microprocessor
    int32 sweepStop;
    
    if (calibratePin_Read() == 0) {
      Serial("Sweeping full output range. Toggle 'Calibrate' switch for \"0-1 V\".");
      sweepV = 65535;
      sweepStop = 0;
    } else {
      sweepV = DAC_VoltsTo_Counts(0.0, *DACRange, *DACOffset);
      sweepStop = DAC_VoltsTo_Counts(1.0, *DACRange, *DACOffset);
      sprintf(serialBuffer, "Sweeping \"0-1 V\" (%ld-%ld). Toggle 'Calibrate' for full range.",
        sweepV, sweepStop);
      Serial(serialBuffer);
    }
    
    // set while loop to false for constant voltage output of channel A
    while(true && sweepV >= sweepStop) {
      fineDAC_SetValue(0x00ff & sweepV);
      coarseDAC_SetValue((0xff00 & sweepV) >> 8);
      sweepV -= 1;
    }
    
    sweepV = DAC_VoltsTo_Counts(1.0, *DACRange, *DACOffset);
    coarseDAC_SetValue((0xff00 & sweepV) >> 8);
    fineDAC_SetValue(0x00ff & sweepV);
   // CyDelay(250);
  }
  
  return;
}