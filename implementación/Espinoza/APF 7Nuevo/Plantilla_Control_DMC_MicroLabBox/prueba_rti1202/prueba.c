/*
 * prueba.c
 *
 * Code generation for model "prueba".
 *
 * Model version              : 1.2
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Tue Apr 16 10:06:45 2019
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "prueba_trc_ptr.h"
#include "prueba.h"
#include "prueba_private.h"

/* Block signals (default storage) */
B_prueba_T prueba_B;

/* Block states (default storage) */
DW_prueba_T prueba_DW;

/* Real-time model */
RT_MODEL_prueba_T prueba_M_;
RT_MODEL_prueba_T *const prueba_M = &prueba_M_;

/* Model output function */
void prueba_output(void)
{
  /* S-Function (rti_commonblock): '<S1>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- prueba/ADC_CLASS1_BL1 --- */
  /* --- [RTI120X, ADC C1] - Channel: 1 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_1, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_1);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_1, readStateFlag, (real_T*)
      &prueba_B.SFunction1);
  }
}

/* Model update function */
void prueba_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++prueba_M->Timing.clockTick0)) {
    ++prueba_M->Timing.clockTickH0;
  }

  prueba_M->Timing.taskTime0 = prueba_M->Timing.clockTick0 *
    prueba_M->Timing.stepSize0 + prueba_M->Timing.clockTickH0 *
    prueba_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void prueba_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)prueba_M, 0,
                sizeof(RT_MODEL_prueba_T));
  prueba_M->Timing.stepSize0 = 1.0E-6;

  /* block I/O */
  {
    prueba_B.SFunction1 = 0.0;
  }

  /* states (dwork) */
  (void) memset((void *)&prueba_DW, 0,
                sizeof(DW_prueba_T));

  {
    /* user code (registration function declaration) */
    /*Initialize global TRC pointers. */
    prueba_rti_init_trc_pointers();
  }
}

/* Model terminate function */
void prueba_terminate(void)
{
  /* (no terminate code required) */
}
