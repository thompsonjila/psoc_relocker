#include "cytypes.h"
#include <stdbool.h>

void Serial(const char8 string[]);
void SendDataArray(int16 data[], int arrayLength, int lastSet, int thresh1, int thresh2);
int32 LFOutADC_VoltsTo_Counts(float volts);
int16 errMonADC_VoltsTo_Counts(float volts);
int32 DAC_VoltsTo_Counts(float volts, float DACRange, int DACOffset);
void setupFreeSoc(bool TEST_VOLTAGE_MODE, int *LFRange, int *DAC150mVLevel, int *DACOffset,
  float *DACRange);
