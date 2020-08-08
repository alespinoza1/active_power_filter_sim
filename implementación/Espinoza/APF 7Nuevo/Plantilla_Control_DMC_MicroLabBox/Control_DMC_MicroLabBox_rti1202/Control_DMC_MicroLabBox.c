/*
 * Control_DMC_MicroLabBox.c
 *
 * Code generation for model "Control_DMC_MicroLabBox".
 *
 * Model version              : 1.144
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Fri Jun  7 14:46:00 2019
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Control_DMC_MicroLabBox_trc_ptr.h"
#include "Control_DMC_MicroLabBox_capi.h"
#include "Control_DMC_MicroLabBox.h"
#include "Control_DMC_MicroLabBox_private.h"

/* Block signals (default storage) */
B_Control_DMC_MicroLabBox_T Control_DMC_MicroLabBox_B;

/* Block states (default storage) */
DW_Control_DMC_MicroLabBox_T Control_DMC_MicroLabBox_DW;

/* Real-time model */
RT_MODEL_Control_DMC_MicroLab_T Control_DMC_MicroLabBox_M_;
RT_MODEL_Control_DMC_MicroLab_T *const Control_DMC_MicroLabBox_M =
  &Control_DMC_MicroLabBox_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/* Model output function */
void Control_DMC_MicroLabBox_output(void)
{
  real_T rtb_Sum;
  real_T rtb_Sum1;
  real_T rtb_Sum2;
  real_T rtb_Sum3;
  real_T rtb_Sum4;
  real_T rtb_Sum5;
  real_T rtb_Sum6;
  real_T rtb_Sum7;
  real_T rtb_Sum8;
  real_T tmp;

  /* Gain: '<S19>/Gain' incorporates:
   *  Memory: '<S19>/Memory'
   */
  Control_DMC_MicroLabBox_B.Gain = Control_DMC_MicroLabBox_P.Gain_Gain *
    Control_DMC_MicroLabBox_DW.Memory_PreviousInput;

  /* Switch: '<S19>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<S19>/Constant1'
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory1'
   *  RelationalOperator: '<S19>/Relational Operator'
   */
  if (Control_DMC_MicroLabBox_DW.Memory1_PreviousInput >=
      Control_DMC_MicroLabBox_P.Constant_Value) {
    tmp = Control_DMC_MicroLabBox_P.Gain1_Gain *
      Control_DMC_MicroLabBox_DW.Memory1_PreviousInput;
  } else {
    tmp = Control_DMC_MicroLabBox_P.Constant1_Value;
  }

  /* End of Switch: '<S19>/Switch' */

  /* Sum: '<S19>/Sum' incorporates:
   *  Constant: '<S19>/Constant'
   *  Memory: '<S19>/Memory1'
   */
  Control_DMC_MicroLabBox_B.Sum = (tmp +
    Control_DMC_MicroLabBox_P.Constant_Value_b) +
    Control_DMC_MicroLabBox_DW.Memory1_PreviousInput;

  /* S-Function (rti_commonblock): '<S28>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsa --- */
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
      &Control_DMC_MicroLabBox_B.SFunction1);
  }

  /* Sum: '<S6>/Sum' incorporates:
   *  Constant: '<S6>/Constant'
   *  Gain: '<S6>/Gain'
   */
  rtb_Sum = Control_DMC_MicroLabBox_P.Ganancia_Vsa *
    Control_DMC_MicroLabBox_B.SFunction1 - Control_DMC_MicroLabBox_P.Vsa_offset;

  /* S-Function (rti_commonblock): '<S29>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsb --- */
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
      &Control_DMC_MicroLabBox_B.SFunction1_h);
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Constant: '<S6>/Constant1'
   *  Gain: '<S6>/Gain1'
   */
  rtb_Sum1 = Control_DMC_MicroLabBox_P.Ganancia_Vsb *
    Control_DMC_MicroLabBox_B.SFunction1_h -
    Control_DMC_MicroLabBox_P.Vsb_offset;

  /* S-Function (rti_commonblock): '<S30>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsc --- */
  /* --- [RTI120X, ADC C1] - Channel: 3 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_3, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_3);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_3, readStateFlag, (real_T*)
      &Control_DMC_MicroLabBox_B.SFunction1_c);
  }

  /* Sum: '<S6>/Sum2' incorporates:
   *  Constant: '<S6>/Constant2'
   *  Gain: '<S6>/Gain2'
   */
  rtb_Sum2 = Control_DMC_MicroLabBox_P.Ganancia_Vsc *
    Control_DMC_MicroLabBox_B.SFunction1_c -
    Control_DMC_MicroLabBox_P.Vsc_offset;

  /* S-Function (rti_commonblock): '<S22>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILa --- */
  /* --- [RTI120X, ADC C1] - Channel: 9 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_9, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_9);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_9, readStateFlag, (real_T*)
      &Control_DMC_MicroLabBox_B.SFunction1_n);
  }

  /* Sum: '<S6>/Sum3' incorporates:
   *  Constant: '<S6>/Constant3'
   *  Gain: '<S6>/Gain3'
   */
  rtb_Sum3 = Control_DMC_MicroLabBox_P.Ganancia_Ila *
    Control_DMC_MicroLabBox_B.SFunction1_n -
    Control_DMC_MicroLabBox_P.Ila_offset;

  /* S-Function (rti_commonblock): '<S23>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILb  --- */
  /* --- [RTI120X, ADC C1] - Channel: 10 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_10, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_10);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_10, readStateFlag,
      (real_T*) &Control_DMC_MicroLabBox_B.SFunction1_o);
  }

  /* Sum: '<S6>/Sum4' incorporates:
   *  Constant: '<S6>/Constant4'
   *  Gain: '<S6>/Gain4'
   */
  rtb_Sum4 = Control_DMC_MicroLabBox_P.Ganancia_Ilb *
    Control_DMC_MicroLabBox_B.SFunction1_o -
    Control_DMC_MicroLabBox_P.Ilb_offset;

  /* S-Function (rti_commonblock): '<S24>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILc --- */
  /* --- [RTI120X, ADC C1] - Channel: 11 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_11, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_11);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_11, readStateFlag,
      (real_T*) &Control_DMC_MicroLabBox_B.SFunction1_f);
  }

  /* Sum: '<S6>/Sum5' incorporates:
   *  Constant: '<S6>/Constant5'
   *  Gain: '<S6>/Gain5'
   */
  rtb_Sum5 = Control_DMC_MicroLabBox_P.Ganancia_Ilc *
    Control_DMC_MicroLabBox_B.SFunction1_f -
    Control_DMC_MicroLabBox_P.Ilc_offset;

  /* S-Function (rti_commonblock): '<S25>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/Ica --- */
  /* --- [RTI120X, ADC C1] - Channel: 17 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_17, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_17);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_17, readStateFlag,
      (real_T*) &Control_DMC_MicroLabBox_B.SFunction1_j);
  }

  /* Sum: '<S6>/Sum6' incorporates:
   *  Constant: '<S6>/Constant6'
   *  Gain: '<S6>/Gain6'
   */
  rtb_Sum6 = Control_DMC_MicroLabBox_P.Ganancia_Ica *
    Control_DMC_MicroLabBox_B.SFunction1_j -
    Control_DMC_MicroLabBox_P.Ica_offset;

  /* S-Function (rti_commonblock): '<S26>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/Icb --- */
  /* --- [RTI120X, ADC C1] - Channel: 18 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_18, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_18);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_18, readStateFlag,
      (real_T*) &Control_DMC_MicroLabBox_B.SFunction1_l);
  }

  /* Sum: '<S6>/Sum7' incorporates:
   *  Constant: '<S6>/Constant7'
   *  Gain: '<S6>/Gain7'
   */
  rtb_Sum7 = Control_DMC_MicroLabBox_P.Ganancia_Icb *
    Control_DMC_MicroLabBox_B.SFunction1_l -
    Control_DMC_MicroLabBox_P.Icb_offset;

  /* S-Function (rti_commonblock): '<S27>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Mediciones1/Icc --- */
  /* --- [RTI120X, ADC C1] - Channel: 19 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_19, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_19);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_19, readStateFlag,
      (real_T*) &Control_DMC_MicroLabBox_B.SFunction1_ng);
  }

  /* Sum: '<S6>/Sum8' incorporates:
   *  Constant: '<S6>/Constant8'
   *  Gain: '<S6>/Gain8'
   */
  rtb_Sum8 = Control_DMC_MicroLabBox_P.Ganancia_Icc *
    Control_DMC_MicroLabBox_B.SFunction1_ng -
    Control_DMC_MicroLabBox_P.Icc_offset;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtControladorInport1' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S1>/Constant3'
   *  Constant: '<S1>/Constant4'
   */
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[0] =
    Control_DMC_MicroLabBox_P.Ts;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[1] = rtb_Sum;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[2] = rtb_Sum1;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[3] = rtb_Sum2;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[4] = rtb_Sum3;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[5] = rtb_Sum4;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[6] = rtb_Sum5;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[7] = rtb_Sum6;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[8] = rtb_Sum7;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[9] = rtb_Sum8;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[10] =
    Control_DMC_MicroLabBox_P.Rc;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[11] =
    Control_DMC_MicroLabBox_P.Lc;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[12] =
    Control_DMC_MicroLabBox_P.Vdc;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[13] =
    Control_DMC_MicroLabBox_P.vect;

  /* S-Function (Control_APF_algoritmo): '<S1>/Controlador' */
  Control_APF_algoritmo_Outputs_wrapper
    (&Control_DMC_MicroLabBox_B.TmpSignalConversionAtControlado[0],
     &Control_DMC_MicroLabBox_B.contador[0],
     &Control_DMC_MicroLabBox_B.Controlador_o2[0],
     &Control_DMC_MicroLabBox_B.Controlador_o3[0],
     &Control_DMC_MicroLabBox_B.Controlador_o4[0],
     &Control_DMC_MicroLabBox_B.Controlador_o5[0],
     &Control_DMC_MicroLabBox_B.Controlador_o6[0],
     &Control_DMC_MicroLabBox_B.Controlador_o7[0],
     &Control_DMC_MicroLabBox_B.Controlador_o8[0],
     &Control_DMC_MicroLabBox_B.Controlador_o9);

  /* Logic: '<S4>/NOT' */
  Control_DMC_MicroLabBox_B.NOT = !(Control_DMC_MicroLabBox_B.contador[0] != 0.0);

  /* S-Function (rti_commonblock): '<S34>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 12 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 12-12 on port 1 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT) << (12 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_12, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_12);
  }

  /* Logic: '<S4>/NOT1' */
  Control_DMC_MicroLabBox_B.NOT1 = !(Control_DMC_MicroLabBox_B.contador[1] !=
    0.0);

  /* S-Function (rti_commonblock): '<S35>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF1 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 11 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 11-11 on port 1 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT1) << (11 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_11, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_11);
  }

  /* Logic: '<S4>/NOT2' */
  Control_DMC_MicroLabBox_B.NOT2 = !(Control_DMC_MicroLabBox_B.contador[2] !=
    0.0);

  /* S-Function (rti_commonblock): '<S36>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF2 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 3 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 3-3 on port 1 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT2) << (3 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_3, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_3);
  }

  /* Logic: '<S4>/NOT3' */
  Control_DMC_MicroLabBox_B.NOT3 = !(Control_DMC_MicroLabBox_B.contador[3] !=
    0.0);

  /* S-Function (rti_commonblock): '<S37>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF3 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 2 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 2-2 on port 1 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT3) << (2 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_2, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_2);
  }

  /* Logic: '<S4>/NOT4' */
  Control_DMC_MicroLabBox_B.NOT4 = !(Control_DMC_MicroLabBox_B.contador[4] !=
    0.0);

  /* S-Function (rti_commonblock): '<S38>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF4 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 4 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 4-4 on port 2 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT4) << (4 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_4, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_4);
  }

  /* Logic: '<S4>/NOT5' */
  Control_DMC_MicroLabBox_B.NOT5 = !(Control_DMC_MicroLabBox_B.contador[5] !=
    0.0);

  /* S-Function (rti_commonblock): '<S39>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 2 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 2-2 on port 2 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT5) << (2 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_2, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_2);
  }

  /* Logic: '<S5>/NOT' */
  Control_DMC_MicroLabBox_B.NOT_l = !(Control_DMC_MicroLabBox_B.Controlador_o9
    != 0.0);

  /* S-Function (rti_commonblock): '<S9>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 3 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 3-3 on port 3 */
    outputData = ( ( ( (UInt32)Control_DMC_MicroLabBox_B.NOT_l) << (3 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_3_Ch_3, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_3_Ch_3);
  }

  /* S-Function (seguidor3): '<S10>/S-Function Builder1' */
  seguidor3_Outputs_wrapper(&Control_DMC_MicroLabBox_B.contador[0],
    &Control_DMC_MicroLabBox_B.Vec_SW[0]);

  /* S-Function (seguidor4): '<S11>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o2[0],
    &Control_DMC_MicroLabBox_B.io[0]);

  /* S-Function (seguidor4): '<S12>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o3[0],
    &Control_DMC_MicroLabBox_B.fc[0]);

  /* TransportDelay: '<S1>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &Control_DMC_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &Control_DMC_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[3];
    real_T simTime = Control_DMC_MicroLabBox_M->Timing.t[0];
    real_T tMinusDelay ;

    {
      int_T i1;
      real_T *y0 = &Control_DMC_MicroLabBox_B.TransportDelay[0];
      int_T *iw_Tail = &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[0];
      int_T *iw_Head = &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0];
      int_T *iw_Last = &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Last[0];
      int_T *iw_CircularBufSize =
        &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[0];
      for (i1=0; i1 < 3; i1++) {
        tMinusDelay = ((Control_DMC_MicroLabBox_P.Tm > 0.0) ?
                       Control_DMC_MicroLabBox_P.Tm : 0.0);
        tMinusDelay = simTime - tMinusDelay;
        y0[i1] = rt_TDelayInterpolate(
          tMinusDelay,
          0.0,
          *tBuffer,
          *uBuffer,
          iw_CircularBufSize[i1],
          &iw_Last[i1],
          iw_Tail[i1],
          iw_Head[i1],
          Control_DMC_MicroLabBox_P.TransportDelay_InitOutput,
          1,
          0);
        tBuffer++;
        uBuffer++;
      }
    }
  }

  /* S-Function (seguidor4): '<S13>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_DMC_MicroLabBox_B.TransportDelay[0],
    &Control_DMC_MicroLabBox_B.icref[0]);

  /* S-Function (seguidor_2S): '<S14>/S-Function Builder1' */
  seguidor_2S_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o6[0],
    &Control_DMC_MicroLabBox_B.PLQL[0]);

  /* S-Function (seguidor_2S): '<S15>/S-Function Builder1' */
  seguidor_2S_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o5[0],
    &Control_DMC_MicroLabBox_B.ilalfabeta[0]);

  /* S-Function (seguidor_2S): '<S16>/S-Function Builder1' */
  seguidor_2S_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o4[0],
    &Control_DMC_MicroLabBox_B.vsalfabeta[0]);

  /* S-Function (seguidor4): '<S17>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o8[0],
    &Control_DMC_MicroLabBox_B.ickm1[0]);

  /* S-Function (seguidor_1S): '<S18>/S-Function Builder1' */
  seguidor_1S_Outputs_wrapper(&Control_DMC_MicroLabBox_B.Controlador_o9,
    &Control_DMC_MicroLabBox_B.bandera);

  /* SignalConversion: '<S6>/TmpSignal ConversionAtS-Function Builder1Inport1' */
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctionB[0] = rtb_Sum;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctionB[1] = rtb_Sum1;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctionB[2] = rtb_Sum2;

  /* S-Function (seguidor): '<S6>/S-Function Builder1' */
  seguidor_Outputs_wrapper
    (&Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctionB[0],
     &Control_DMC_MicroLabBox_B.Vs_med[0]);

  /* SignalConversion: '<S6>/TmpSignal ConversionAtS-Function BuilderInport1' */
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[0] = rtb_Sum3;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[1] = rtb_Sum4;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[2] = rtb_Sum5;

  /* S-Function (seguidor): '<S6>/S-Function Builder' */
  seguidor_Outputs_wrapper
    (&Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[0],
     &Control_DMC_MicroLabBox_B.IL_med[0]);

  /* SignalConversion: '<S6>/TmpSignal ConversionAtS-Function Builder2Inport1' */
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[0] = rtb_Sum6;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[1] = rtb_Sum7;
  Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[2] = rtb_Sum8;

  /* S-Function (seguidor): '<S6>/S-Function Builder2' */
  seguidor_Outputs_wrapper
    (&Control_DMC_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[0],
     &Control_DMC_MicroLabBox_B.Ic_med[0]);

  /* S-Function (rti_commonblock): '<S21>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* End of Outputs for S-Function (rti_commonblock): '<S21>/S-Function1' */

  /* S-Function (rti_commonblock): '<S20>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* S-Function (rti_commonblock): '<S3>/S-Function1' incorporates:
   *  Constant: '<Root>/Duty Cycle'
   *  Constant: '<Root>/Period'
   */
  /* This comment workarounds a code generation problem */

  /* --- Control_DMC_MicroLabBox/DIO_CLASS1_PWM_BL1 --- */
  /* --- [RTI120X, PWM OUT] - Port: 3 - Channel: 1 --- */

  /* write PWM Period and DutyCycle for output channel 1 on port 3 */
  DioCl1PwmOut_setPeriod(pRTIDioC1PwmOut_Port_3_Ch_1, (real_T)
    Control_DMC_MicroLabBox_P.Ts);
  DioCl1PwmOut_setDutyCycle(pRTIDioC1PwmOut_Port_3_Ch_1, (real_T)
    Control_DMC_MicroLabBox_P.DutyCycle_Value);
  DioCl1PwmOut_write(pRTIDioC1PwmOut_Port_3_Ch_1);
}

/* Model update function */
void Control_DMC_MicroLabBox_update(void)
{
  /* Update for Memory: '<S19>/Memory' */
  Control_DMC_MicroLabBox_DW.Memory_PreviousInput =
    Control_DMC_MicroLabBox_B.Gain;

  /* Update for Memory: '<S19>/Memory1' */
  Control_DMC_MicroLabBox_DW.Memory1_PreviousInput =
    Control_DMC_MicroLabBox_B.Sum;

  /* Update for TransportDelay: '<S1>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &Control_DMC_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &Control_DMC_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[3];
    real_T simTime = Control_DMC_MicroLabBox_M->Timing.t[0];
    Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0] =
      ((Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0] <
        (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[0]-1)) ?
       (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0]+1) : 0);
    if (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0] ==
        Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[0]) {
      Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[0] =
        ((Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[0] <
          (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[0]-1))
         ? (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[0]+1) : 0);
    }

    (*tBuffer++)[Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0]] =
      simTime;
    (*uBuffer++)[Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0]] =
      Control_DMC_MicroLabBox_B.Controlador_o7[0];
    Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[1] =
      ((Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[1] <
        (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[1]-1)) ?
       (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[1]+1) : 0);
    if (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[1] ==
        Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[1]) {
      Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[1] =
        ((Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[1] <
          (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[1]-1))
         ? (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[1]+1) : 0);
    }

    (*tBuffer++)[Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[1]] =
      simTime;
    (*uBuffer++)[Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[1]] =
      Control_DMC_MicroLabBox_B.Controlador_o7[1];
    Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[2] =
      ((Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[2] <
        (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[2]-1)) ?
       (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[2]+1) : 0);
    if (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[2] ==
        Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[2]) {
      Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[2] =
        ((Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[2] <
          (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[2]-1))
         ? (Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[2]+1) : 0);
    }

    (*tBuffer)[Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[2]] =
      simTime;
    (*uBuffer)[Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[2]] =
      Control_DMC_MicroLabBox_B.Controlador_o7[2];
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Control_DMC_MicroLabBox_M->Timing.clockTick0)) {
    ++Control_DMC_MicroLabBox_M->Timing.clockTickH0;
  }

  Control_DMC_MicroLabBox_M->Timing.t[0] =
    Control_DMC_MicroLabBox_M->Timing.clockTick0 *
    Control_DMC_MicroLabBox_M->Timing.stepSize0 +
    Control_DMC_MicroLabBox_M->Timing.clockTickH0 *
    Control_DMC_MicroLabBox_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [1.0E-6s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 1.0E-6, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    Control_DMC_MicroLabBox_M->Timing.clockTick1++;
    if (!Control_DMC_MicroLabBox_M->Timing.clockTick1) {
      Control_DMC_MicroLabBox_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void Control_DMC_MicroLabBox_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Control_DMC_MicroLabBox_M, 0,
                sizeof(RT_MODEL_Control_DMC_MicroLab_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Control_DMC_MicroLabBox_M->solverInfo,
                          &Control_DMC_MicroLabBox_M->Timing.simTimeStep);
    rtsiSetTPtr(&Control_DMC_MicroLabBox_M->solverInfo, &rtmGetTPtr
                (Control_DMC_MicroLabBox_M));
    rtsiSetStepSizePtr(&Control_DMC_MicroLabBox_M->solverInfo,
                       &Control_DMC_MicroLabBox_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Control_DMC_MicroLabBox_M->solverInfo,
                          (&rtmGetErrorStatus(Control_DMC_MicroLabBox_M)));
    rtsiSetRTModelPtr(&Control_DMC_MicroLabBox_M->solverInfo,
                      Control_DMC_MicroLabBox_M);
  }

  rtsiSetSimTimeStep(&Control_DMC_MicroLabBox_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&Control_DMC_MicroLabBox_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Control_DMC_MicroLabBox_M,
             &Control_DMC_MicroLabBox_M->Timing.tArray[0]);
  Control_DMC_MicroLabBox_M->Timing.stepSize0 = 1.0E-6;

  /* block I/O */
  (void) memset(((void *) &Control_DMC_MicroLabBox_B), 0,
                sizeof(B_Control_DMC_MicroLabBox_T));

  /* states (dwork) */
  (void) memset((void *)&Control_DMC_MicroLabBox_DW, 0,
                sizeof(DW_Control_DMC_MicroLabBox_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Control_DMC_MicroLabBox_InitializeDataMapInfo();

  {
    /* user code (registration function declaration) */
    /*Initialize global TRC pointers. */
    Control_DMC_MicroLabBox_rti_init_trc_pointers();
  }

  /* Start for TransportDelay: '<S1>/Transport Delay' */
  {
    real_T *pBuffer =
      &Control_DMC_MicroLabBox_DW.TransportDelay_RWORK.TUbufferArea[0];

    {
      int_T i1;
      int_T *iw_Tail = &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Tail[0];
      int_T *iw_Head = &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Head[0];
      int_T *iw_Last = &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.Last[0];
      int_T *iw_CircularBufSize =
        &Control_DMC_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize[0];
      void **pw_TUbufferPtrs =
        &Control_DMC_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      for (i1=0; i1 < 3; i1++) {
        iw_Tail[i1] = 0;
        iw_Head[i1] = 0;
        iw_Last[i1] = 0;
        iw_CircularBufSize[i1] = 1024;
        pBuffer[0] = Control_DMC_MicroLabBox_P.TransportDelay_InitOutput;
        pBuffer[1024] = Control_DMC_MicroLabBox_M->Timing.t[0];
        pw_TUbufferPtrs[i1] = (void *) &pBuffer[0];
        pw_TUbufferPtrs[i1+3] = (void *) &pBuffer[1024];
        pBuffer += 2048;
      }
    }
  }

  /* InitializeConditions for Memory: '<S19>/Memory' */
  Control_DMC_MicroLabBox_DW.Memory_PreviousInput =
    Control_DMC_MicroLabBox_P.Memory_InitialCondition;

  /* InitializeConditions for Memory: '<S19>/Memory1' */
  Control_DMC_MicroLabBox_DW.Memory1_PreviousInput =
    Control_DMC_MicroLabBox_P.Memory1_InitialCondition;
}

/* Model terminate function */
void Control_DMC_MicroLabBox_terminate(void)
{
  /* Terminate for S-Function (rti_commonblock): '<S34>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 12 --- */

  /* disable digital output channel 12-12 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_12,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_12);

  /* Terminate for S-Function (rti_commonblock): '<S35>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF1 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 11 --- */

  /* disable digital output channel 11-11 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_11,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_11);

  /* Terminate for S-Function (rti_commonblock): '<S36>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF2 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 3 --- */

  /* disable digital output channel 3-3 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_3,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_3);

  /* Terminate for S-Function (rti_commonblock): '<S37>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF3 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 2 --- */

  /* disable digital output channel 2-2 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_2,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_2);

  /* Terminate for S-Function (rti_commonblock): '<S38>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF4 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 4 --- */

  /* disable digital output channel 4-4 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_4,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_4);

  /* Terminate for S-Function (rti_commonblock): '<S39>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 2 --- */

  /* disable digital output channel 2-2 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_2,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_2);

  /* Terminate for S-Function (rti_commonblock): '<S9>/S-Function1' */

  /* --- Control_DMC_MicroLabBox/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 3 --- */

  /* disable digital output channel 3-3 on port 3 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_3_Ch_3,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_3_Ch_3);

  /* Terminate for S-Function (rti_commonblock): '<S3>/S-Function1' incorporates:
   *  Constant: '<Root>/Duty Cycle'
   *  Constant: '<Root>/Period'
   */

  /* --- Control_DMC_MicroLabBox/DIO_CLASS1_PWM_BL1 --- */
  /* --- [RTI120X, PWM OUT] - Port: 3 - Channel: 1 --- */

  /* disable digital output channel 1 on port 3 *
   * (set to high-impedance), when the simulation terminates */
  DioCl1PwmOut_setOutputHighZ(pRTIDioC1PwmOut_Port_3_Ch_1, DIO_CLASS1_HIGH_Z_ON);
  DioCl1PwmOut_write(pRTIDioC1PwmOut_Port_3_Ch_1);
}
