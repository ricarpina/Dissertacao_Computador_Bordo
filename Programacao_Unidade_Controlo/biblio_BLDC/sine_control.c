#include <math.h>
#include "sine_control.h"

#define configBLDC_MAX_SINE_LUT_VALUE (100)
#define configNUM_SINE_LUT_ENTRIES (50)

float sineWaveLut[configNUM_SINE_LUT_ENTRIES] = {0};

//! @brief Populates the sine LUT
//! @details The sine LUT is placed in RAM for fast access.
//! Call as part of the initialisation sequence.
//! Shifts sinewave so that values never go negative,
//! making it easy in ISR to multiply by scaling factor to get duty cycle
//! @note Not thread-safe. Call from Bldc_MainTask() only.
//! @private
void Bldc_FillSineLut(void)
{
   int i, configPI=3.14;
   // Populate LUT
   for(i = 0; i < configNUM_SINE_LUT_ENTRIES; i++)
   {
      double radians = (((float)i/(float)configNUM_SINE_LUT_ENTRIES)*360.0)*(configPI/180.0);
      sineWaveLut[i] = ((configBLDC_MAX_SINE_LUT_VALUE/2.0)*sin(radians) + (configBLDC_MAX_SINE_LUT_VALUE/2.0))/(configBLDC_MAX_SINE_LUT_VALUE/2);
   }
}

