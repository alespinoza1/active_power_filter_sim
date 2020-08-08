/*
 * testMicrolabBox.c
 *
 * Code generation for model "testMicrolabBox".
 *
 * Model version              : 1.7
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Fri Mar 15 15:02:42 2019
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "testMicrolabBox_trc_ptr.h"
#include "testMicrolabBox_capi.h"
#include "testMicrolabBox.h"
#include "testMicrolabBox_private.h"

/* Block signals (default storage) */
B_testMicrolabBox_T testMicrolabBox_B;

/* Real-time model */
RT_MODEL_testMicrolabBox_T testMicrolabBox_M_;
RT_MODEL_testMicrolabBox_T *const testMicrolabBox_M = &testMicrolabBox_M_;

/* Model output function */
void testMicrolabBox_output(void)
{
  real_T u0;

  /* S-Function (rti_commonblock): '<S1>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- testMicrolabBox/ADC_CLASS1_BL1 --- */
  /* --- [RTI120X, ADC C1] - Channel: 2 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_2, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_2);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_2, readStateFlag, (real_T*)
      &testMicrolabBox_B.SFunction1);
  }

  /* Gain: '<Root>/Gain1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Sum: '<Root>/Sum'
   */
  u0 = (testMicrolabBox_P.Constant_Value + testMicrolabBox_B.SFunction1) *
    testMicrolabBox_P.Gain1_Gain;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > testMicrolabBox_P.Saturation_UpperSat) {
    testMicrolabBox_B.Saturation = testMicrolabBox_P.Saturation_UpperSat;
  } else if (u0 < testMicrolabBox_P.Saturation_LowerSat) {
    testMicrolabBox_B.Saturation = testMicrolabBox_P.Saturation_LowerSat;
  } else {
    testMicrolabBox_B.Saturation = u0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* S-Function (rti_commonblock): '<S2>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- testMicrolabBox/DAC_CLASS1_BL1 --- */
  /* --- [RTI120X, DAC C1] - Channel: 2 --- */
  {
    /* define variables required for DAC realtime functions */
    Float64 inportDacData= 0.0;
    inportDacData = (real_T) testMicrolabBox_B.Saturation;

    /* write value of CL1 DAC for output channel 2 */
    DacCl1AnalogOut_setOutputValue(pRTIDacC1AnalogOut_Ch_2, DAC_CLASS1_CHANNEL_2,
      inportDacData);
    DacCl1AnalogOut_write(pRTIDacC1AnalogOut_Ch_2);
  }

  /* S-Function (duplicar): '<Root>/S-Function Builder' */
  duplicar_Outputs_wrapper(&testMicrolabBox_B.SFunction1,
    &testMicrolabBox_B.sal2);

  /* Gain: '<Root>/Gain2' */
  u0 = testMicrolabBox_P.Gain2_Gain * testMicrolabBox_B.sal2;

  /* Saturate: '<Root>/Saturation1' */
  if (u0 > testMicrolabBox_P.Saturation1_UpperSat) {
    testMicrolabBox_B.Saturation1 = testMicrolabBox_P.Saturation1_UpperSat;
  } else if (u0 < testMicrolabBox_P.Saturation1_LowerSat) {
    testMicrolabBox_B.Saturation1 = testMicrolabBox_P.Saturation1_LowerSat;
  } else {
    testMicrolabBox_B.Saturation1 = u0;
  }

  /* End of Saturate: '<Root>/Saturation1' */

  /* S-Function (rti_commonblock): '<S3>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- testMicrolabBox/DAC_CLASS1_BL2 --- */
  /* --- [RTI120X, DAC C1] - Channel: 1 --- */
  {
    /* define variables required for DAC realtime functions */
    Float64 inportDacData= 0.0;
    inportDacData = (real_T) testMicrolabBox_B.Saturation1;

    /* write value of CL1 DAC for output channel 1 */
    DacCl1AnalogOut_setOutputValue(pRTIDacC1AnalogOut_Ch_1, DAC_CLASS1_CHANNEL_1,
      inportDacData);
    DacCl1AnalogOut_write(pRTIDacC1AnalogOut_Ch_1);
  }

  /* S-Function (rti_commonblock): '<S4>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* S-Function (rti_commonblock): '<S5>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- testMicrolabBox/DIO_CLASS1_BIT_OUT_BL1 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 1 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 1-1 on port 3 */
    outputData = ( ( ( (UInt32)testMicrolabBox_B.SFunction1_e) << (1 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_3_Ch_1, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_3_Ch_1);
  }
}

/* Model update function */
void testMicrolabBox_update(void)
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
  if (!(++testMicrolabBox_M->Timing.clockTick0)) {
    ++testMicrolabBox_M->Timing.clockTickH0;
  }

  testMicrolabBox_M->Timing.taskTime0 = testMicrolabBox_M->Timing.clockTick0 *
    testMicrolabBox_M->Timing.stepSize0 + testMicrolabBox_M->Timing.clockTickH0 *
    testMicrolabBox_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void testMicrolabBox_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)testMicrolabBox_M, 0,
                sizeof(RT_MODEL_testMicrolabBox_T));
  testMicrolabBox_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &testMicrolabBox_B), 0,
                sizeof(B_testMicrolabBox_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  testMicrolabBox_InitializeDataMapInfo();

  {
    /* user code (registration function declaration) */
    /*Initialize global TRC pointers. */
    testMicrolabBox_rti_init_trc_pointers();
  }
}

/* Model terminate function */
void testMicrolabBox_terminate(void)
{
  /* Terminate for S-Function (rti_commonblock): '<S2>/S-Function1' */

  /* --- testMicrolabBox/DAC_CLASS1_BL1 --- */
  /* --- [RTI120X, DAC C1] - Channel: 2 --- */

  /* All channel outputs are set to high impedance state */
  DacCl1AnalogOut_setOutputHighZ(pRTIDacC1AnalogOut_Ch_2, DAC_CLASS1_HIGH_Z_ON);

  /* Deactivates AnalogOut functionality */
  DacCl1AnalogOut_stop(pRTIDacC1AnalogOut_Ch_2);

  /* Terminate for S-Function (rti_commonblock): '<S3>/S-Function1' */

  /* --- testMicrolabBox/DAC_CLASS1_BL2 --- */
  /* --- [RTI120X, DAC C1] - Channel: 1 --- */

  /* All channel outputs are set to high impedance state */
  DacCl1AnalogOut_setOutputHighZ(pRTIDacC1AnalogOut_Ch_1, DAC_CLASS1_HIGH_Z_ON);

  /* Deactivates AnalogOut functionality */
  DacCl1AnalogOut_stop(pRTIDacC1AnalogOut_Ch_1);

  /* Terminate for S-Function (rti_commonblock): '<S5>/S-Function1' */

  /* --- testMicrolabBox/DIO_CLASS1_BIT_OUT_BL1 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 1 --- */

  /* disable digital output channel 1-1 on port 3 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_3_Ch_1,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_3_Ch_1);
}
