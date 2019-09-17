/* ================================================================
Automated Laser Frequency Relocking Procedure
Original Programmer: Denton Wu
Last modified: Sept 2018
Notes:

Greetings relocker user or improver. This is the main relocker algorithm.

There are two parts to the code: the setup and the relocking procedure. Because this algorithm
needs the ability to work with three different loop filter output ranges, it offers three 
relocking procedures, one for each loop filter model. The user can cue the box to run any one of
these procedures depending on the loop filter in use. Effectively, these procedures are the same
except for the ADC and DAC voltage limit parameters.

On your journeys through this code, remember: You've got a fast car.
==================================================================*/

#include "project.h"
#include <stdbool.h>

int main(void) {
  /*Variable setup and pin initialization*/
  CyGlobalIntEnable // Enable global interrupts...

  int MAX_FAILS_BEFORE_LED = 5; // relock attempts before red LED turns on
  int SWEEP_DELAY_US = 0; // software delay in microseconds/step to slow sweep
  
  int i = 0;
  int j = 0;
  bool sweptPastThresh = 0;
  bool triggerMode = false;

  int modeOut = 0;
  int upRail = 0;
  int lowRail = 0;
  int sweepHigh = 0;
  double sweepCenter = 0.0;
  int coarseCenter = 0;
  int coarseLow = 0;
  int coarseHigh = 0;
  double fineProp = 0.0;
  int fineCenter = 0;
  int fineLow = 0;
  int fineHigh = 0;

  int nowEMonVal = 4000;
  int lowVal = 4000;
  int dev = 0;
  int thresSubtract = 0;
  int detectThres = 0;

  int fineLoopCounter = 0;
  int fullCoarseLoops;

  int lockFails = 0;

  checkLight_Write(1); // checkLight is the onboard LED (unused)

  yellowLight_Write(0);
  greenLight_Write(0);
  redLight_Write(0);
  switches_Write(0); // writes to all pins attached to 'switches': aPin, bPin, and orangeLight

  eMonADC_Start(); // Begin monitoring error signal monitor ADC

  triggerMode = pin_triggerMode_Read(); // 1 = triggered mode, 0 = automatically relock.
  
  /* When the box is powered, the microprocessor runs the initialization code. The following
  loop prevents the program from moving on until the user sets the "Lock in Range" switch to
  "Lock". Do NOT set the switch until having already selected for the loop filter range. */

  while (lockIn_Read() == 1) {
    CyDelay(50);
  }

  for (;;) {

    /* Once the user sets "Lock in Range" to "Lock", the microprocessor reads in which range the
    user selected via the three channels connecting the microprocessor output level shifter bias
    to the microprocessor on the relocker structure diagram. Each channel is connected to one pin:
    either setting8V, setting22V, or setting28V. Only one of the channels biases up to 5 V. The
    microprocessor enters the loop whose detection pin reads its channel to be high, and whose
    code is written for the relevant loop filter model. */

    while (setting8V_Read() == 1) {
      
      /* Read in the "good" error signal's parameters, and calibrate to relock to those
      parameters. The user should trigger the calibration procedure immediately after locking in
      the loop filter range. Ideally, the user will have preset the "Choose Mode" switch to the
      "Choose position before turning on the box, so the calibration procedure will start
      immediately after range lock in */
      while (calibratePin_Read() == 1) {

        greenLight_Write(0);
        yellowLight_Write(1);

        /* The microprocessor needs two features of the error signal. The first is the signal's
        voltage maximum. This loop measures the maximum and sets lowVal to that maximum, in terms
        of the eMonADC computing parameters. The ADC's lowest reading corresponds to the error
        signal's highest voltage because the error signal level shifter inverts the error signal.
        Flipping the "Error Signal Sampling" switch to "On" triggers the loop. */

        if (thresSample_Read() == 1) {
          eMonADC_StartConvert(); // is this right place for StartConvert? When should we StopConvert?
          nowEMonVal = eMonADC_GetResult16();

          if (nowEMonVal < lowVal) {
            lowVal = nowEMonVal;
          }
        }

        /* Next, we use lowVal to set the detection threshold voltage. The error signal level
        shifter shifts the error signal's 0 V up to 2 V, which corresponds to an ADC parameter of
        2000. This code sets the detection threshold variable, detectThres, to be half the error
        signal maximum value. */

        dev = 2000 - lowVal; // From center value
        thresSubtract = dev / 2;
        detectThres = 2000 - thresSubtract;

        /* After sampling the error signal, the user should lock the system. The second relevant
        error signal feature is the loop filter voltage associated with the centerpoint of the 
        error signal. With the cavity locked, the next three lines can read this in. */

        lfOutADC_Start();
        modeOut = lfOutADC_Read32();

        /* The microprocessor now knows what loop filter output voltage corresponds to "in lock".
        It needs to calculate upper and lower voltage bounds to this lock voltage. These close
        off the region inside of which the microprocessor thinks lock voltage sits. I've chosen to
        set the bounds to be 150mV above and below the in lock voltage, as modes usually don't
        drift any further than this. 150mV corresponds to the ADC parameter 940 in the 8V mode. */

        upRail = modeOut + 940;
        lowRail = modeOut - 940;

        /*Now the fun begins. When attempting to relock, the microprocessor sweeps the loop filter
        output through the region in which it thinks the lock voltage lies. That voltage region is
        the same as the one set above: 150 mV above and below the current loop filter voltage. It
        needs to set its sweep bounds at those voltages as well.
                  
        Unfortunately, the DAC parameters are not the same as the ADC parameters. We need to
        calculate the two DAC parameters (one for the coarseDAC and one for the fineDAC) that
        correspond to the lower sweep bound at -150 mV, and the two DAC parameters that correspond
        to the upper sweep bound at +150 mV. The calculation is a bit involved. Consult the user
        manual for details. The following lines of code calculate the sweep bounds and assign them
        to coarseLow, fineLow, coarseHigh, and fineHigh. */

        sweepCenter = 256 * (((double) modeOut) / ((double) 53595)) - 12;
        /* At times the DAC circuits and ADC circuits can misalign in zero point. We can solve
        this misalignment by offsetting the sweepCenter variable by a few steps, hence the -12. */
        coarseCenter = (int) sweepCenter;
        fineProp = sweepCenter - coarseCenter;
        fineCenter = (int)((fineProp * ((double) 255)) + 0.5);

        if (fineCenter > 203) {
          coarseLow = coarseCenter - 4;
          coarseHigh = coarseCenter + 5;

          fineLow = fineCenter - 204;
          fineHigh = fineCenter - 50;
          /* Set +1 higher than it needs to be for the for loop to sweep through the actual 
          necessary high value */
        } else if (fineCenter > 51 && fineCenter <= 203) {
          coarseLow = coarseCenter - 5;
          coarseHigh = coarseCenter + 5;

          fineLow = fineCenter + 51;
          fineHigh = fineCenter - 50;
          /* Set +1 higher than it needs to be for the for loop to sweep through the actual 
          necessary high value */
        } else {
          coarseLow = coarseCenter - 5;
          coarseHigh = coarseCenter + 4;

          fineLow = fineCenter + 51;
          fineHigh = fineCenter + 205;
          /* Set +1 higher than it needs to be for the for loop to sweep through the actual 
          necessary high value */
        }

        // The sweep boundaries are now assigned.

        fullCoarseLoops = coarseHigh - coarseLow;
        /* This variable tells the code how many full coarseDAC steps the relocker signal spans,
        and thus the number of full fineDAC sweeps to run */
      }

      // Board is watching for a drop while outside the loop below.
      // Board is in relocking mode while inside the loop below.
      yellowLight_Write(0);
      
    
      // Loop filter signal out of range?
      lfOutADC_StartConvert();
      lockFails = 0; // Track how many times we swept without seeing threshold crossed
      while ((lfOutADC_GetResult32() > upRail) || (lfOutADC_GetResult32() < lowRail)) {

        // Switch to ''search mode''
        greenLight_Write(0);
        switches_Write(1);

        sweptPastThresh = false;

        coarseDAC_Start();
        fineDAC_Start();
        eMonADC_StartConvert();

        // The following for-loop is the voltage sweep, comprised of three smaller fineDAC sweeps.
        fineLoopCounter = 0; // For tracking which voltage sweep loop to enter
        for (i = coarseLow; i <= coarseHigh; i++) {
          coarseDAC_SetValue(i);

          // This is the first fineDAC sweep to run. It begins right on fineLow.
          if (fineLoopCounter == 0) {
            for (j = fineLow; j < 256; j++) {
              fineDAC_SetValue(j);

              /* These two if-statements check whether the error signal has crossed in and out of
              the detection. The variable "sweptPastThresh" tracks whether the error signal has
              already passed the detection threshold once. If it is 1 when the error signal passes
              the detection threshold the second time, the microprocessor knows that the error
              signal is back in the central linear region and ready to lock. */

              int16 error_monitor_ADC = eMonADC_GetResult16();
              if (error_monitor_ADC < detectThres) {
                sweptPastThresh = true;
              }
              
              if ((error_monitor_ADC > detectThres) && sweptPastThresh) {
                /* Once the microprocessor sees that the error signal has entered back into its
                linear region, it sets the iteration variables to values that return false for
                both the coarseDAC and fineDAC loop conditions. */
                i = 300;
                j = 300;
              }

              CyDelayUs(SWEEP_DELAY_US);
            }

            fineLoopCounter++;
            /* Adding to fineLoopCounter tells the code that the first fineDAC sweep has already run,
            and that the full sweeps should be run next. It knows how many full sweeps to run
            based on the fullCoarseLoops variable. */
          } else if (fineLoopCounter < fullCoarseLoops) {
            for (j = 0; j < 256; j++) {
              fineDAC_SetValue(j);

              int16 error_monitor_ADC = eMonADC_GetResult16();
              if (error_monitor_ADC < detectThres) {
                sweptPastThresh = true;
              }

              if ((error_monitor_ADC > detectThres) && sweptPastThresh) {
                j = 300;
                i = 300;
              }

              CyDelayUs(SWEEP_DELAY_US);
            }
            fineLoopCounter++;

          } else if (fineLoopCounter == fullCoarseLoops) { // final sweep ends on fineHigh
            for (j = 0; j < fineHigh; j++) {
              fineDAC_SetValue(j);

              int16 error_monitor_ADC = eMonADC_GetResult16();
              if (error_monitor_ADC < detectThres) {
                sweptPastThresh = true;
              }
              
              if ((error_monitor_ADC > detectThres) && sweptPastThresh) {
                j = 300;
                i = 300;
              }
              CyDelayUs(SWEEP_DELAY_US);
            }
            fineLoopCounter++;
          } else { // we have failed to lock on this sweep
            lockFails++;

            if (lockFails == MAX_FAILS_BEFORE_LED) { // If we fail too many times, turn on the red light
              redLight_Write(1);
            }
          }
          
        } // end for: voltage sweep (check if LF is in range)
      } // end while-LF-out-of-range

      /* If we detect the error signal has entered back into its central region, it will exit the
      loop and switch back into the conventional setup now */

      switches_Write(0);
      greenLight_Write(1);
      redLight_Write(0);

      /*This is the end of the relocker code. Beyond this lay the two loops that manage relocking for the 22 V mode and the
      28 V mode. The code for these modes is exactly the same, barring the ADC and DAC parameters that manage detecting
      and relocking the system.*/
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////

    while (setting22V_Read() == 1) {
      while (calibratePin_Read() == 1) {
        greenLight_Write(0);
        yellowLight_Write(1);

        // Reading in the error signal size
        if (thresSample_Read() == 1) {
          eMonADC_StartConvert();
          nowEMonVal = eMonADC_GetResult16();

          if (nowEMonVal < lowVal) {
            lowVal = nowEMonVal;
          }
        }

        dev = 2000 - lowVal; // From center value
        thresSubtract = dev / 2;
        detectThres = 2000 - thresSubtract;

        lfOutADC_Start();

        // Calibrate relocking parameters to prefer mode to which laser is curently locked
        lfOutADC_StartConvert();
        modeOut = lfOutADC_Read32();

        upRail = modeOut + 342;
        lowRail = modeOut - 342;

        sweepCenter = 256 * (((double) modeOut) / ((double) 53595)) - 11;
        coarseCenter = (int) sweepCenter;
        fineProp = sweepCenter - coarseCenter;
        fineCenter = (int)((fineProp * ((double) 255)) + 0.5);

        if (fineCenter > 189) {
          coarseLow = coarseCenter - 2;
          coarseHigh = coarseCenter + 3;
          sweepHigh = coarseCenter + 4;

          fineLow = fineCenter - 190;
          fineHigh = fineCenter - 64;
          /* Set +1 higher than it needs to be for the for loop to sweep through the actual
          necessary high value */
        } else if (fineCenter > 65 && fineCenter <= 189) {
          coarseLow = coarseCenter - 3;
          coarseHigh = coarseCenter + 3;
          sweepHigh = coarseCenter + 4;

          fineLow = fineCenter + 65;
          fineHigh = fineCenter - 64;
          /* Set +1 higher than it needs to be for the for loop to sweep through the actual 
          necessary high value */
        } else {
          coarseLow = coarseCenter - 3;
          coarseHigh = coarseCenter + 2;
          sweepHigh = coarseCenter + 4;

          fineLow = fineCenter + 65;
          fineHigh = fineCenter + 191;
          /* Set +1 higher than it needs to be for the for loop to sweep through the actual
          necessary high value */
        }

        fineLoopCounter = 1;
        fullCoarseLoops = coarseHigh - coarseLow;
      }

      yellowLight_Write(0);

      // Board is in watch mode while outside the loop below.
      // Board is in search mode while inside the loop below.

      lfOutADC_StartConvert();
      while (lfOutADC_GetResult32() > upRail || lfOutADC_GetResult32() < lowRail) {

        // Switch to search mode    

        greenLight_Write(0);
        switches_Write(1);

        sweptPastThresh = 0;
        lockFails = 0;

        coarseDAC_Start();
        fineDAC_Start();
        eMonADC_StartConvert();

        // Sweep laser frequency    

        for (i = coarseLow; i < sweepHigh; i++) {
          coarseDAC_SetValue(i);

          if (fineLoopCounter == 1) {
            for (j = fineLow; j < 256; j++) {
              fineDAC_SetValue(j);

              if (eMonADC_GetResult16() < detectThres)
                sweptPastThresh = 1;

              if (eMonADC_GetResult16() > detectThres && sweptPastThresh == 1) {
                j = 300;
                i = 300;
              }

              CyDelayUs(1);
            }

            fineLoopCounter++;
          } else if (fineLoopCounter <= fullCoarseLoops && fineLoopCounter > 1) {
            for (j = 0; j < 256; j++) {
              fineDAC_SetValue(j);

              if (eMonADC_GetResult16() < detectThres)
                sweptPastThresh = 1;

              if (eMonADC_GetResult16() > detectThres && sweptPastThresh == 1) {
                j = 300;
                i = 300;
              }

              CyDelayUs(1);
            }

            fineLoopCounter++;
          } else {
            for (j = 0; j < fineHigh; j++) {
              fineDAC_SetValue(j);

              if (eMonADC_GetResult16() < detectThres)
                sweptPastThresh = 1;

              if (eMonADC_GetResult16() > detectThres && sweptPastThresh == 1) {
                j = 300;
                i = 300;
              }

              CyDelayUs(1);
            }

            fineLoopCounter = 1;
          }

          if (i == coarseHigh) {
            i = (coarseLow - 1);
            lockFails++;

            if (lockFails == 20) {
              redLight_Write(1);
              lockFails--;
            }
          }
        }
      }

      // Switch to watch mode

      fineLoopCounter = 1;
      switches_Write(0);
      greenLight_Write(1);
      redLight_Write(0);
    }

    while (setting28V_Read() == 1) {
      while (calibratePin_Read() == 1) {
        greenLight_Write(0);
        yellowLight_Write(1);

        // Reading in the error signal size
        if (thresSample_Read() == 1) {
          eMonADC_StartConvert();
          nowEMonVal = eMonADC_GetResult16();

          if (nowEMonVal < lowVal) {
            lowVal = nowEMonVal;
          }
        }

        dev = 2000 - lowVal; // From center value
        thresSubtract = dev / 2;
        detectThres = 2000 - thresSubtract;

        lfOutADC_Start();

        // Calibrate relocking parameters to prefer mode to which laser is curently locked
        lfOutADC_StartConvert();
        modeOut = lfOutADC_Read32();

        upRail = modeOut + 269;
        lowRail = modeOut - 269;

        sweepCenter = 256 * (((double) modeOut) / ((double) 53595));
        coarseCenter = (int) sweepCenter;
        fineProp = sweepCenter - coarseCenter;
        fineCenter = (int)((fineProp * ((double) 255)) + 0.5);

        if (fineCenter > 160) {
          coarseLow = coarseCenter - 1;
          coarseHigh = coarseCenter + 2;
          sweepHigh = coarseCenter + 3;

          fineLow = fineCenter - 95;
          fineHigh = fineCenter - 159;
          /*Set +1 higher than it needs to be for 
                                                         the for loop to sweep through the actual
                                                         necessary high value*/
        } else if (fineCenter > 94 && fineCenter <= 159) {
          coarseLow = coarseCenter - 1;
          coarseHigh = coarseCenter + 1;
          sweepHigh = coarseCenter + 2;

          fineLow = fineCenter - 95;
          fineHigh = fineCenter + 96;
          /*Set +1 higher than it needs to be for 
                                                         the for loop to sweep through the actual
                                                         necessary high value*/
        } else {
          coarseLow = coarseCenter - 2;
          coarseHigh = coarseCenter + 1;
          sweepHigh = coarseCenter + 2;

          fineLow = fineCenter + 160;
          fineHigh = fineCenter + 95;
          // Set +1 higher than it needs to be for the for loop to sweep through the actual necessary high value
        }

        fineLoopCounter = 1;
        fullCoarseLoops = coarseHigh - coarseLow;
      }

      yellowLight_Write(0);

      // Board is in watch mode while outside the loop below.
      // Board is in search mode while inside the loop below.

      lfOutADC_StartConvert();

      while (lfOutADC_GetResult32() > upRail || lfOutADC_GetResult32() < lowRail) {

        // Switch to search mode    

        greenLight_Write(0);
        switches_Write(1);

        sweptPastThresh = 0;
        lockFails = 0;

        coarseDAC_Start();
        fineDAC_Start();
        eMonADC_StartConvert();

        // Sweep laser frequency    

        for (i = coarseLow; i < sweepHigh; i++) {
          coarseDAC_SetValue(i);

          if (fineLoopCounter == 1) {
            for (j = fineLow; j < 256; j++) {
              fineDAC_SetValue(j);

              if (eMonADC_GetResult16() < detectThres)
                sweptPastThresh = 1;

              if (eMonADC_GetResult16() > detectThres && sweptPastThresh == 1) {
                j = 300;
                i = 300;
              }

              CyDelayUs(1);
            }

            fineLoopCounter++;
          } else if (fineLoopCounter <= fullCoarseLoops && fineLoopCounter > 1) {
            for (j = 0; j < 256; j++) {
              fineDAC_SetValue(j);

              if (eMonADC_GetResult16() < detectThres)
                sweptPastThresh = 1;

              if (eMonADC_GetResult16() > detectThres && sweptPastThresh == 1) {
                j = 300;
                i = 300;
              }

              CyDelayUs(1);
            }

            fineLoopCounter++;
          } else {
            for (j = 0; j < fineHigh; j++) {
              fineDAC_SetValue(j);

              if (eMonADC_GetResult16() < detectThres)
                sweptPastThresh = 1;

              if (eMonADC_GetResult16() > detectThres && sweptPastThresh == 1) {
                j = 300;
                i = 300;
              }

              CyDelayUs(1);
            }

            fineLoopCounter = 1;
          }

          if (i == coarseHigh) {
            i = (coarseLow - 1);
            lockFails++;

            if (lockFails == 20) {
              redLight_Write(1);
              lockFails--;
            }
          }

          CyDelayUs(1);
        }
      }

      // Switch to watch mode

      fineLoopCounter = 1;
      switches_Write(0);
      greenLight_Write(1);
      redLight_Write(0);
    }
  }
}

/* You got a fast car
I want a ticket to anywhere
Maybe we make a deal
Maybe together we can get somewhere
Anyplace is better
Starting from zero got nothing to lose
Maybe we'll make something
Me, myself I got nothing to prove */