/*
 * Control_APF7_MicroLabBox.c
 *
 * Code generation for model "Control_APF7_MicroLabBox".
 *
 * Model version              : 1.319
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Fri Jul 24 16:44:51 2020
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Control_APF7_MicroLabBox_trc_ptr.h"
#include "Control_APF7_MicroLabBox_capi.h"
#include "Control_APF7_MicroLabBox.h"
#include "Control_APF7_MicroLabBox_private.h"

/* Block signals (default storage) */
B_Control_APF7_MicroLabBox_T Control_APF7_MicroLabBox_B;

/* Block states (default storage) */
DW_Control_APF7_MicroLabBox_T Control_APF7_MicroLabBox_DW;

/* Real-time model */
RT_MODEL_Control_APF7_MicroLa_T Control_APF7_MicroLabBox_M_;
RT_MODEL_Control_APF7_MicroLa_T *const Control_APF7_MicroLabBox_M =
  &Control_APF7_MicroLabBox_M_;

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

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T u1_0;
  if (rtIsNaN(u0) || rtIsInf(u0) || (rtIsNaN(u1) || rtIsInf(u1))) {
    y = (rtNaN);
  } else {
    if (u1 < 0.0) {
      u1_0 = ceil(u1);
    } else {
      u1_0 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = fabs(u0 / u1);
      if (fabs(u1_0 - floor(u1_0 + 0.5)) <= DBL_EPSILON * u1_0) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/* Model output function */
void Control_APF7_MicroLabBox_output(void)
{
  /* local block i/o variables */
  real_T rtb_TransportDelay;
  real_T rtb_TransportDelay1;
  real_T rtb_Gain;
  real_T rtb_Gain10;
  real_T rtb_Gain11;
  real_T rtb_Gain12;
  real_T rtb_Gain13;
  real_T rtb_Gain14;
  real_T rtb_Gain15;
  real_T rtb_Gain17;
  real_T rtb_Gain18;
  boolean_T rtb_RelationalOperator_b;
  boolean_T rtb_RelationalOperator2;
  boolean_T rtb_RelationalOperator_h2;
  boolean_T rtb_RelationalOperator2_k;
  boolean_T rtb_RelationalOperator_h;
  boolean_T rtb_RelationalOperator2_e;
  boolean_T rtb_RelationalOperator_d;
  boolean_T rtb_RelationalOperator2_c;
  boolean_T rtb_RelationalOperator_a;
  boolean_T rtb_RelationalOperator2_n;
  boolean_T rtb_RelationalOperator_io;
  boolean_T rtb_RelationalOperator2_i;
  boolean_T rtb_RelationalOperator_jq;
  boolean_T rtb_RelationalOperator2_g;
  boolean_T rtb_RelationalOperator_j;
  boolean_T rtb_RelationalOperator2_a;
  boolean_T rtb_RelationalOperator_ko;
  boolean_T rtb_RelationalOperator2_b;
  real_T rtb_Sum3;
  real_T rtb_Sum4;
  real_T rtb_Sum5;
  real_T tmp;

  /* Gain: '<S9>/Gain' incorporates:
   *  Memory: '<S9>/Memory'
   */
  Control_APF7_MicroLabBox_B.Gain = Control_APF7_MicroLabBox_P.Gain_Gain *
    Control_APF7_MicroLabBox_DW.Memory_PreviousInput;

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Gain: '<S9>/Gain1'
   *  Memory: '<S9>/Memory1'
   *  RelationalOperator: '<S9>/Relational Operator'
   */
  if (Control_APF7_MicroLabBox_DW.Memory1_PreviousInput >=
      Control_APF7_MicroLabBox_P.Constant_Value) {
    tmp = Control_APF7_MicroLabBox_P.Gain1_Gain *
      Control_APF7_MicroLabBox_DW.Memory1_PreviousInput;
  } else {
    tmp = Control_APF7_MicroLabBox_P.Constant1_Value;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Sum: '<S9>/Sum' incorporates:
   *  Constant: '<S9>/Constant'
   *  Memory: '<S9>/Memory1'
   */
  Control_APF7_MicroLabBox_B.Sum = (tmp +
    Control_APF7_MicroLabBox_P.Constant_Value_b) +
    Control_APF7_MicroLabBox_DW.Memory1_PreviousInput;

  /* S-Function (rti_commonblock): '<S24>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/Vsa --- */
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
      &Control_APF7_MicroLabBox_B.SFunction1);
  }

  /* Gain: '<S4>/Gain' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain9'
   *  Sum: '<S4>/Sum'
   */
  rtb_Gain = (Control_APF7_MicroLabBox_P.Gain9_Gain *
              Control_APF7_MicroLabBox_B.SFunction1 -
              Control_APF7_MicroLabBox_P.Vsa_offset) *
    -Control_APF7_MicroLabBox_P.Ganancia_Vsa;

  /* S-Function (rti_commonblock): '<S25>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/Vsb --- */
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
      &Control_APF7_MicroLabBox_B.SFunction1_h);
  }

  /* Gain: '<S4>/Gain10' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Gain: '<S4>/Gain1'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Gain10 = (Control_APF7_MicroLabBox_P.Gain1_Gain_d *
                Control_APF7_MicroLabBox_B.SFunction1_h -
                Control_APF7_MicroLabBox_P.Vsb_offset) *
    -Control_APF7_MicroLabBox_P.Ganancia_Vsb;

  /* S-Function (rti_commonblock): '<S26>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/Vsc --- */
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
      &Control_APF7_MicroLabBox_B.SFunction1_c);
  }

  /* Gain: '<S4>/Gain11' incorporates:
   *  Constant: '<S4>/Constant2'
   *  Gain: '<S4>/Gain2'
   *  Sum: '<S4>/Sum2'
   */
  rtb_Gain11 = (Control_APF7_MicroLabBox_P.Gain2_Gain *
                Control_APF7_MicroLabBox_B.SFunction1_c -
                Control_APF7_MicroLabBox_P.Vsc_offset) *
    -Control_APF7_MicroLabBox_P.Ganancia_Vsc;

  /* S-Function (rti_commonblock): '<S18>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/ILa --- */
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
      &Control_APF7_MicroLabBox_B.SFunction1_n);
  }

  /* Sum: '<S4>/Sum3' incorporates:
   *  Constant: '<S4>/Constant3'
   *  Gain: '<S4>/Gain3'
   */
  rtb_Sum3 = Control_APF7_MicroLabBox_P.Ganancia_Ila *
    Control_APF7_MicroLabBox_B.SFunction1_n -
    Control_APF7_MicroLabBox_P.Ila_offset;

  /* S-Function (rti_commonblock): '<S19>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/ILb  --- */
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
      (real_T*) &Control_APF7_MicroLabBox_B.SFunction1_o);
  }

  /* Sum: '<S4>/Sum4' incorporates:
   *  Constant: '<S4>/Constant4'
   *  Gain: '<S4>/Gain4'
   */
  rtb_Sum4 = Control_APF7_MicroLabBox_P.Ganancia_Ilb *
    Control_APF7_MicroLabBox_B.SFunction1_o -
    Control_APF7_MicroLabBox_P.Ilb_offset;

  /* S-Function (rti_commonblock): '<S20>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/ILc --- */
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
      (real_T*) &Control_APF7_MicroLabBox_B.SFunction1_f);
  }

  /* Sum: '<S4>/Sum5' incorporates:
   *  Constant: '<S4>/Constant5'
   *  Gain: '<S4>/Gain5'
   */
  rtb_Sum5 = Control_APF7_MicroLabBox_P.Ganancia_Ilc *
    Control_APF7_MicroLabBox_B.SFunction1_f -
    Control_APF7_MicroLabBox_P.Ilc_offset;

  /* S-Function (rti_commonblock): '<S21>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/Ica --- */
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
      (real_T*) &Control_APF7_MicroLabBox_B.SFunction1_j);
  }

  /* Gain: '<S4>/Gain12' incorporates:
   *  Constant: '<S4>/Constant6'
   *  Gain: '<S4>/Gain6'
   *  Sum: '<S4>/Sum6'
   */
  rtb_Gain12 = (Control_APF7_MicroLabBox_P.Ganancia_Ica *
                Control_APF7_MicroLabBox_B.SFunction1_j -
                Control_APF7_MicroLabBox_P.Ica_offset) *
    Control_APF7_MicroLabBox_P.Gain12_Gain;

  /* S-Function (rti_commonblock): '<S22>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/Icb --- */
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
      (real_T*) &Control_APF7_MicroLabBox_B.SFunction1_l);
  }

  /* Gain: '<S4>/Gain13' incorporates:
   *  Constant: '<S4>/Constant7'
   *  Gain: '<S4>/Gain7'
   *  Sum: '<S4>/Sum7'
   */
  rtb_Gain13 = (Control_APF7_MicroLabBox_P.Ganancia_Icb *
                Control_APF7_MicroLabBox_B.SFunction1_l -
                Control_APF7_MicroLabBox_P.Icb_offset) *
    Control_APF7_MicroLabBox_P.Gain13_Gain;

  /* S-Function (rti_commonblock): '<S23>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/Icc --- */
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
      (real_T*) &Control_APF7_MicroLabBox_B.SFunction1_ng);
  }

  /* Gain: '<S4>/Gain14' incorporates:
   *  Constant: '<S4>/Constant8'
   *  Gain: '<S4>/Gain8'
   *  Sum: '<S4>/Sum8'
   */
  rtb_Gain14 = (Control_APF7_MicroLabBox_P.Ganancia_Icc *
                Control_APF7_MicroLabBox_B.SFunction1_ng -
                Control_APF7_MicroLabBox_P.Icc_offset) *
    Control_APF7_MicroLabBox_P.Gain14_Gain;

  /* S-Function (rti_commonblock): '<S27>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/dclink1 --- */
  /* --- [RTI120X, ADC C1] - Channel: 4 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_4, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_4);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_4, readStateFlag, (real_T*)
      &Control_APF7_MicroLabBox_B.SFunction1_b);
  }

  /* Gain: '<S4>/Gain15' */
  rtb_Gain15 = Control_APF7_MicroLabBox_P.Gain15_Gain *
    Control_APF7_MicroLabBox_B.SFunction1_b;

  /* S-Function (rti_commonblock): '<S28>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/dclink2 --- */
  /* --- [RTI120X, ADC C1] - Channel: 5 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_5, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_5);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_5, readStateFlag, (real_T*)
      &Control_APF7_MicroLabBox_B.SFunction1_i);
  }

  /* Gain: '<S4>/Gain17' */
  rtb_Gain17 = Control_APF7_MicroLabBox_P.Gain17_Gain *
    Control_APF7_MicroLabBox_B.SFunction1_i;

  /* S-Function (rti_commonblock): '<S29>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Mediciones1/dclink3 --- */
  /* --- [RTI120X, ADC C1] - Channel: 6 --- */
  {
    UInt32 readStateFlag[] = { 1 };

    /* define variable required for adc cl1 realtime functions */
    UInt32 IsNew = 0;

    /* wait until conversion result is available */
    while (IsNew == 0) {
      AdcCl1AnalogIn_isDataReady(pRTIAdcC1AnalogIn_Ch_6, &IsNew);
    }

    /* read conversion result from hardware */
    AdcCl1AnalogIn_read(pRTIAdcC1AnalogIn_Ch_6);

    /* retrieve conversion result */
    AdcCl1AnalogIn_getSingleValue(pRTIAdcC1AnalogIn_Ch_6, readStateFlag, (real_T*)
      &Control_APF7_MicroLabBox_B.SFunction1_jc);
  }

  /* Gain: '<S4>/Gain18' */
  rtb_Gain18 = Control_APF7_MicroLabBox_P.Gain18_Gain *
    Control_APF7_MicroLabBox_B.SFunction1_jc;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtControladorInport1' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant10'
   *  Constant: '<S1>/Constant11'
   *  Constant: '<S1>/Constant12'
   *  Constant: '<S1>/Constant13'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S1>/Constant3'
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Constant5'
   *  Constant: '<S1>/Constant6'
   *  Constant: '<S1>/Constant7'
   *  Constant: '<S1>/Constant8'
   *  Constant: '<S1>/Constant9'
   */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[0] =
    Control_APF7_MicroLabBox_P.Ts;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[1] = rtb_Gain;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[2] = rtb_Gain10;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[3] = rtb_Gain11;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[4] = rtb_Sum3;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[5] = rtb_Sum4;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[6] = rtb_Sum5;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[7] = rtb_Gain12;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[8] = rtb_Gain13;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[9] = rtb_Gain14;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[10] =
    Control_APF7_MicroLabBox_P.Rc;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[11] =
    Control_APF7_MicroLabBox_P.Lc;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[12] =
    Control_APF7_MicroLabBox_P.Vdc;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[13] = rtb_Gain15;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[14] = rtb_Gain17;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[15] = rtb_Gain18;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[16] =
    Control_APF7_MicroLabBox_P.kp;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[17] =
    Control_APF7_MicroLabBox_P.ki;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[18] =
    Control_APF7_MicroLabBox_P.lamda;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[19] =
    Control_APF7_MicroLabBox_P.z;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[20] =
    Control_APF7_MicroLabBox_P.e;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[21] =
    Control_APF7_MicroLabBox_P.g;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[22] =
    Control_APF7_MicroLabBox_P.f;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[23] =
    Control_APF7_MicroLabBox_P.x;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[24] =
    Control_APF7_MicroLabBox_P.y;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[25] =
    Control_APF7_MicroLabBox_P.sat;

  /* S-Function (Control_APF7_algoritmo): '<S1>/Controlador' */
  Control_APF7_algoritmo_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtControlado[0],
     &Control_APF7_MicroLabBox_B.contador[0],
     &Control_APF7_MicroLabBox_B.Controlador_o2[0],
     &Control_APF7_MicroLabBox_B.Controlador_o3[0],
     &Control_APF7_MicroLabBox_B.Controlador_o4[0],
     &Control_APF7_MicroLabBox_B.Controlador_o5[0],
     &Control_APF7_MicroLabBox_B.Controlador_o6[0],
     &Control_APF7_MicroLabBox_B.Controlador_o7[0],
     &Control_APF7_MicroLabBox_B.Controlador_o8[0],
     &Control_APF7_MicroLabBox_B.Controlador_o9[0],
     &Control_APF7_MicroLabBox_B.Controlador_o10[0]);

  /* S-Function (seguidor_2S): '<S5>/S-Function Builder1' */
  seguidor_2S_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o6[0],
    &Control_APF7_MicroLabBox_B.PLQL[0]);

  /* S-Function (seguidor_2S): '<S6>/S-Function Builder1' */
  seguidor_2S_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o7[0],
    &Control_APF7_MicroLabBox_B.Qc_Qs[0]);

  /* SignalConversion: '<S45>/Output' incorporates:
   *  Clock: '<S45>/Clock'
   *  Constant: '<S45>/Constant'
   *  Lookup_n-D: '<S45>/Look-Up Table1'
   *  Math: '<S45>/Math Function'
   *  S-Function (sfun_tstart): '<S45>/startTime'
   *  Sum: '<S45>/Sum'
   */
  Control_APF7_MicroLabBox_B.Output = look1_binlxpw(rt_remd_snf
    (Control_APF7_MicroLabBox_M->Timing.t[0] - (0.0),
     Control_APF7_MicroLabBox_P.Constant_Value_g),
    Control_APF7_MicroLabBox_P.LookUpTable1_bp01Data,
    Control_APF7_MicroLabBox_P.RepeatingSequence1_rep_seq_y, 2U);

  /* RelationalOperator: '<S36>/Relational Operator' */
  rtb_RelationalOperator_b = (Control_APF7_MicroLabBox_B.Output <=
    Control_APF7_MicroLabBox_B.Controlador_o4[0]);

  /* Gain: '<S36>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1 = Control_APF7_MicroLabBox_P.Gain1_Gain_f *
    Control_APF7_MicroLabBox_B.Controlador_o4[0];

  /* RelationalOperator: '<S36>/Relational Operator2' */
  rtb_RelationalOperator2 = (Control_APF7_MicroLabBox_B.Output <=
    Control_APF7_MicroLabBox_B.Gain1);

  /* TransportDelay: '<S8>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = Control_APF7_MicroLabBox_M->Timing.t[0];
    real_T tMinusDelay = simTime - (Control_APF7_MicroLabBox_P.Ts * 0.166667);
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize,
      &Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Last,
      Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail,
      Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head,
      Control_APF7_MicroLabBox_P.TransportDelay_InitOutput,
      0,
      0);
  }

  /* RelationalOperator: '<S37>/Relational Operator' */
  rtb_RelationalOperator_h2 = (rtb_TransportDelay <=
    Control_APF7_MicroLabBox_B.Controlador_o4[0]);

  /* Gain: '<S37>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_j = Control_APF7_MicroLabBox_P.Gain1_Gain_c *
    Control_APF7_MicroLabBox_B.Controlador_o4[0];

  /* RelationalOperator: '<S37>/Relational Operator2' */
  rtb_RelationalOperator2_k = (rtb_TransportDelay <=
    Control_APF7_MicroLabBox_B.Gain1_j);

  /* TransportDelay: '<S8>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay1_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay1_PWORK.TUbufferPtrs[1];
    real_T simTime = Control_APF7_MicroLabBox_M->Timing.t[0];
    real_T tMinusDelay = simTime - (( Control_APF7_MicroLabBox_P.Ts * 0.333333 ));
    rtb_TransportDelay1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.CircularBufSize,
      &Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Last,
      Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Tail,
      Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head,
      Control_APF7_MicroLabBox_P.TransportDelay1_InitOutput,
      0,
      0);
  }

  /* RelationalOperator: '<S38>/Relational Operator' */
  rtb_RelationalOperator_h = (rtb_TransportDelay1 <=
    Control_APF7_MicroLabBox_B.Controlador_o4[0]);

  /* Gain: '<S38>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_m = Control_APF7_MicroLabBox_P.Gain1_Gain_e *
    Control_APF7_MicroLabBox_B.Controlador_o4[0];

  /* RelationalOperator: '<S38>/Relational Operator2' */
  rtb_RelationalOperator2_e = (rtb_TransportDelay1 <=
    Control_APF7_MicroLabBox_B.Gain1_m);

  /* SignalConversion: '<S46>/TmpSignal ConversionAtS-Function Builder1Inport1' incorporates:
   *  DataTypeConversion: '<S36>/Data Type Conversion'
   *  DataTypeConversion: '<S36>/Data Type Conversion3'
   *  DataTypeConversion: '<S37>/Data Type Conversion'
   *  DataTypeConversion: '<S37>/Data Type Conversion3'
   *  DataTypeConversion: '<S38>/Data Type Conversion'
   *  DataTypeConversion: '<S38>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[0] =
    rtb_RelationalOperator_b;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[1] =
    rtb_RelationalOperator2;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[2] =
    rtb_RelationalOperator_h2;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[3] =
    rtb_RelationalOperator2_k;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[4] =
    rtb_RelationalOperator_h;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[5] =
    rtb_RelationalOperator2_e;

  /* S-Function (seguidor3): '<S46>/S-Function Builder1' */
  seguidor3_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctionB[0],
     &Control_APF7_MicroLabBox_B.Vec_SWA[0]);

  /* RelationalOperator: '<S39>/Relational Operator' */
  rtb_RelationalOperator_d = (Control_APF7_MicroLabBox_B.Output <=
    Control_APF7_MicroLabBox_B.Controlador_o4[1]);

  /* Gain: '<S39>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_h = Control_APF7_MicroLabBox_P.Gain1_Gain_fe *
    Control_APF7_MicroLabBox_B.Controlador_o4[1];

  /* RelationalOperator: '<S39>/Relational Operator2' */
  rtb_RelationalOperator2_c = (Control_APF7_MicroLabBox_B.Output <=
    Control_APF7_MicroLabBox_B.Gain1_h);

  /* RelationalOperator: '<S40>/Relational Operator' */
  rtb_RelationalOperator_a = (rtb_TransportDelay <=
    Control_APF7_MicroLabBox_B.Controlador_o4[1]);

  /* Gain: '<S40>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_n = Control_APF7_MicroLabBox_P.Gain1_Gain_h *
    Control_APF7_MicroLabBox_B.Controlador_o4[1];

  /* RelationalOperator: '<S40>/Relational Operator2' */
  rtb_RelationalOperator2_n = (rtb_TransportDelay <=
    Control_APF7_MicroLabBox_B.Gain1_n);

  /* RelationalOperator: '<S41>/Relational Operator' */
  rtb_RelationalOperator_io = (rtb_TransportDelay1 <=
    Control_APF7_MicroLabBox_B.Controlador_o4[1]);

  /* Gain: '<S41>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_d = Control_APF7_MicroLabBox_P.Gain1_Gain_d1 *
    Control_APF7_MicroLabBox_B.Controlador_o4[1];

  /* RelationalOperator: '<S41>/Relational Operator2' */
  rtb_RelationalOperator2_i = (rtb_TransportDelay1 <=
    Control_APF7_MicroLabBox_B.Gain1_d);

  /* SignalConversion: '<S47>/TmpSignal ConversionAtS-Function Builder1Inport1' incorporates:
   *  DataTypeConversion: '<S39>/Data Type Conversion'
   *  DataTypeConversion: '<S39>/Data Type Conversion3'
   *  DataTypeConversion: '<S40>/Data Type Conversion'
   *  DataTypeConversion: '<S40>/Data Type Conversion3'
   *  DataTypeConversion: '<S41>/Data Type Conversion'
   *  DataTypeConversion: '<S41>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[0] =
    rtb_RelationalOperator_d;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[1] =
    rtb_RelationalOperator2_c;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[2] =
    rtb_RelationalOperator_a;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[3] =
    rtb_RelationalOperator2_n;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[4] =
    rtb_RelationalOperator_io;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[5] =
    rtb_RelationalOperator2_i;

  /* S-Function (seguidor3): '<S47>/S-Function Builder1' */
  seguidor3_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_i[0],
     &Control_APF7_MicroLabBox_B.Vec_SWB[0]);

  /* RelationalOperator: '<S42>/Relational Operator' */
  rtb_RelationalOperator_jq = (Control_APF7_MicroLabBox_B.Output <=
    Control_APF7_MicroLabBox_B.Controlador_o4[2]);

  /* Gain: '<S42>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_f = Control_APF7_MicroLabBox_P.Gain1_Gain_o *
    Control_APF7_MicroLabBox_B.Controlador_o4[2];

  /* RelationalOperator: '<S42>/Relational Operator2' */
  rtb_RelationalOperator2_g = (Control_APF7_MicroLabBox_B.Output <=
    Control_APF7_MicroLabBox_B.Gain1_f);

  /* RelationalOperator: '<S43>/Relational Operator' */
  rtb_RelationalOperator_j = (rtb_TransportDelay <=
    Control_APF7_MicroLabBox_B.Controlador_o4[2]);

  /* Gain: '<S43>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_c = Control_APF7_MicroLabBox_P.Gain1_Gain_g *
    Control_APF7_MicroLabBox_B.Controlador_o4[2];

  /* RelationalOperator: '<S43>/Relational Operator2' */
  rtb_RelationalOperator2_a = (rtb_TransportDelay <=
    Control_APF7_MicroLabBox_B.Gain1_c);

  /* RelationalOperator: '<S44>/Relational Operator' */
  rtb_RelationalOperator_ko = (rtb_TransportDelay1 <=
    Control_APF7_MicroLabBox_B.Controlador_o4[2]);

  /* Gain: '<S44>/Gain1' */
  Control_APF7_MicroLabBox_B.Gain1_dv = Control_APF7_MicroLabBox_P.Gain1_Gain_cv
    * Control_APF7_MicroLabBox_B.Controlador_o4[2];

  /* RelationalOperator: '<S44>/Relational Operator2' */
  rtb_RelationalOperator2_b = (rtb_TransportDelay1 <=
    Control_APF7_MicroLabBox_B.Gain1_dv);

  /* SignalConversion: '<S48>/TmpSignal ConversionAtS-Function Builder1Inport1' incorporates:
   *  DataTypeConversion: '<S42>/Data Type Conversion'
   *  DataTypeConversion: '<S42>/Data Type Conversion3'
   *  DataTypeConversion: '<S43>/Data Type Conversion'
   *  DataTypeConversion: '<S43>/Data Type Conversion3'
   *  DataTypeConversion: '<S44>/Data Type Conversion'
   *  DataTypeConversion: '<S44>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[0] =
    rtb_RelationalOperator_jq;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[1] =
    rtb_RelationalOperator2_g;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[2] =
    rtb_RelationalOperator_j;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[3] =
    rtb_RelationalOperator2_a;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[4] =
    rtb_RelationalOperator_ko;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[5] =
    rtb_RelationalOperator2_b;

  /* S-Function (seguidor3): '<S48>/S-Function Builder1' */
  seguidor3_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_ig[0],
     &Control_APF7_MicroLabBox_B.Vec_SWC[0]);

  /* Logic: '<S33>/NOT4' incorporates:
   *  DataTypeConversion: '<S38>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT4 = !rtb_RelationalOperator_h;

  /* S-Function (rti_commonblock): '<S52>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 11 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 11-11 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT4) << (11 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_11, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_11);
  }

  /* Logic: '<S33>/NOT5' incorporates:
   *  DataTypeConversion: '<S38>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT5 = !rtb_RelationalOperator2_e;

  /* S-Function (rti_commonblock): '<S53>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF1 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 12 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 12-12 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT5) << (12 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_12, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_12);
  }

  /* Logic: '<S33>/NOT' incorporates:
   *  DataTypeConversion: '<S36>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT = !rtb_RelationalOperator_b;

  /* S-Function (rti_commonblock): '<S54>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF10 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 15 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 15-15 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT) << (15 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_15, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_15);
  }

  /* Logic: '<S33>/NOT3' incorporates:
   *  DataTypeConversion: '<S37>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT3 = !rtb_RelationalOperator2_k;

  /* S-Function (rti_commonblock): '<S55>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF7 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 13 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 13-13 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT3) << (13 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_13, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_13);
  }

  /* Logic: '<S33>/NOT2' incorporates:
   *  DataTypeConversion: '<S37>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT2 = !rtb_RelationalOperator_h2;

  /* S-Function (rti_commonblock): '<S56>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF8 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 14 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 14-14 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT2) << (14 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_14, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_14);
  }

  /* Logic: '<S33>/NOT1' incorporates:
   *  DataTypeConversion: '<S36>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT1 = !rtb_RelationalOperator2;

  /* S-Function (rti_commonblock): '<S57>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF9 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 16 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 16-16 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT1) << (16 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_16, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_16);
  }

  /* Logic: '<S34>/NOT' incorporates:
   *  DataTypeConversion: '<S39>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT_h = !rtb_RelationalOperator_d;

  /* S-Function (rti_commonblock): '<S58>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF10 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 7 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 7-7 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT_h) << (7 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_7, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_7);
  }

  /* Logic: '<S34>/NOT4' incorporates:
   *  DataTypeConversion: '<S41>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT4_e = !rtb_RelationalOperator_io;

  /* S-Function (rti_commonblock): '<S59>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF2 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 2 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 2-2 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT4_e) << (2 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_2, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_2);
  }

  /* Logic: '<S34>/NOT5' incorporates:
   *  DataTypeConversion: '<S41>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT5_a = !rtb_RelationalOperator2_i;

  /* S-Function (rti_commonblock): '<S60>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF3 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 3 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 3-3 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT5_a) << (3 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_3, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_3);
  }

  /* Logic: '<S34>/NOT3' incorporates:
   *  DataTypeConversion: '<S40>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT3_k = !rtb_RelationalOperator2_n;

  /* S-Function (rti_commonblock): '<S61>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF7 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 4 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 4-4 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT3_k) << (4 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_4, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_4);
  }

  /* Logic: '<S34>/NOT2' incorporates:
   *  DataTypeConversion: '<S40>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT2_i = !rtb_RelationalOperator_a;

  /* S-Function (rti_commonblock): '<S62>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF8 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 5 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 5-5 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT2_i) << (5 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_5, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_5);
  }

  /* Logic: '<S34>/NOT1' incorporates:
   *  DataTypeConversion: '<S39>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT1_m = !rtb_RelationalOperator2_c;

  /* S-Function (rti_commonblock): '<S63>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF9 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 6 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 6-6 on port 1 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT1_m) << (6 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_6, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_6);
  }

  /* Logic: '<S35>/NOT' incorporates:
   *  DataTypeConversion: '<S42>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT_b = !rtb_RelationalOperator_jq;

  /* S-Function (rti_commonblock): '<S64>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF10 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 8 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 8-8 on port 2 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT_b) << (8 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_8, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_8);
  }

  /* Logic: '<S35>/NOT4' incorporates:
   *  DataTypeConversion: '<S44>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT4_h = !rtb_RelationalOperator_ko;

  /* S-Function (rti_commonblock): '<S65>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF4 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 2 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 2-2 on port 2 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT4_h) << (2 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_2, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_2);
  }

  /* Logic: '<S35>/NOT5' incorporates:
   *  DataTypeConversion: '<S44>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT5_p = !rtb_RelationalOperator2_b;

  /* S-Function (rti_commonblock): '<S66>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF6 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 4 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 4-4 on port 2 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT5_p) << (4 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_4, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_4);
  }

  /* Logic: '<S35>/NOT3' incorporates:
   *  DataTypeConversion: '<S43>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT3_f = !rtb_RelationalOperator2_a;

  /* S-Function (rti_commonblock): '<S67>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF7 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 5 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 5-5 on port 2 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT3_f) << (5 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_5, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_5);
  }

  /* Logic: '<S35>/NOT2' incorporates:
   *  DataTypeConversion: '<S43>/Data Type Conversion'
   */
  Control_APF7_MicroLabBox_B.NOT2_b = !rtb_RelationalOperator_j;

  /* S-Function (rti_commonblock): '<S68>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF8 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 6 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 6-6 on port 2 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT2_b) << (6 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_6, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_6);
  }

  /* Logic: '<S35>/NOT1' incorporates:
   *  DataTypeConversion: '<S42>/Data Type Conversion3'
   */
  Control_APF7_MicroLabBox_B.NOT1_b = !rtb_RelationalOperator2_g;

  /* S-Function (rti_commonblock): '<S69>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF9 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 7 --- */
  {
    /* define variables required for BitOut realtime functions */
    UInt32 outputData = 0;

    /* write output state value to digital output channel 7-7 on port 2 */
    outputData = ( ( ( (UInt32)Control_APF7_MicroLabBox_B.NOT1_b) << (7 - 1)) |
                  outputData);
    DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_7, outputData);
    DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_7);
  }

  /* S-Function (seguidor12): '<S11>/S-Function Builder1' */
  seguidor12_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o10[0],
    &Control_APF7_MicroLabBox_B.varfiltrada[0]);

  /* S-Function (seguidor4): '<S12>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o4[0],
    &Control_APF7_MicroLabBox_B.fc[0]);

  /* S-Function (seguidor4): '<S13>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o8[0],
    &Control_APF7_MicroLabBox_B.ickm1[0]);

  /* S-Function (seguidor4): '<S14>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o9[0],
    &Control_APF7_MicroLabBox_B.icref[0]);

  /* S-Function (seguidor4): '<S15>/S-Function Builder1' */
  seguidor4_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o2[0],
    &Control_APF7_MicroLabBox_B.ploss[0]);

  /* S-Function (seguidor_2S): '<S16>/S-Function Builder1' */
  seguidor_2S_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Controlador_o5[0],
    &Control_APF7_MicroLabBox_B.vsalfabeta[0]);

  /* SignalConversion: '<S4>/TmpSignal ConversionAtS-Function Builder1Inport1' */
  Control_APF7_MicroLabBox_B.Vs_med[0] = rtb_Gain;
  Control_APF7_MicroLabBox_B.Vs_med[1] = rtb_Gain10;
  Control_APF7_MicroLabBox_B.Vs_med[2] = rtb_Gain11;

  /* S-Function (seguidor): '<S4>/S-Function Builder1' */
  seguidor_Outputs_wrapper(&Control_APF7_MicroLabBox_B.Vs_med[0],
    &Control_APF7_MicroLabBox_B.Vs_med_j[0]);

  /* SignalConversion: '<S4>/TmpSignal ConversionAtS-Function BuilderInport1' */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[0] = rtb_Sum3;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[1] = rtb_Sum4;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[2] = rtb_Sum5;

  /* S-Function (seguidor): '<S4>/S-Function Builder' */
  seguidor_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_f[0],
     &Control_APF7_MicroLabBox_B.IL_med[0]);

  /* SignalConversion: '<S4>/TmpSignal ConversionAtS-Function Builder2Inport1' */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[0] = rtb_Gain12;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[1] = rtb_Gain13;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[2] = rtb_Gain14;

  /* S-Function (seguidor): '<S4>/S-Function Builder2' */
  seguidor_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFunctio_h[0],
     &Control_APF7_MicroLabBox_B.Ic_med[0]);

  /* SignalConversion: '<S4>/TmpSignal ConversionAtS-Function Builder3Inport1' */
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_iv[0] = rtb_Gain15;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_iv[1] = rtb_Gain17;
  Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_iv[2] = rtb_Gain18;

  /* S-Function (seguidor): '<S4>/S-Function Builder3' */
  seguidor_Outputs_wrapper
    (&Control_APF7_MicroLabBox_B.TmpSignalConversionAtSFuncti_iv[0],
     &Control_APF7_MicroLabBox_B.Vdclink[0]);

  /* S-Function (rti_commonblock): '<S17>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* End of Outputs for S-Function (rti_commonblock): '<S17>/S-Function1' */

  /* S-Function (rti_commonblock): '<S10>/S-Function1' */
  /* This comment workarounds a code generation problem */

  /* S-Function (rti_commonblock): '<S3>/S-Function1' incorporates:
   *  Constant: '<Root>/Duty Cycle'
   *  Constant: '<Root>/Period'
   */
  /* This comment workarounds a code generation problem */

  /* --- Control_APF7_MicroLabBox/DIO_CLASS1_PWM_BL1 --- */
  /* --- [RTI120X, PWM OUT] - Port: 3 - Channel: 1 --- */

  /* write PWM Period and DutyCycle for output channel 1 on port 3 */
  DioCl1PwmOut_setPeriod(pRTIDioC1PwmOut_Port_3_Ch_1, (real_T)
    Control_APF7_MicroLabBox_P.Ts);
  DioCl1PwmOut_setDutyCycle(pRTIDioC1PwmOut_Port_3_Ch_1, (real_T)
    Control_APF7_MicroLabBox_P.DutyCycle_Value);
  DioCl1PwmOut_write(pRTIDioC1PwmOut_Port_3_Ch_1);
}

/* Model update function */
void Control_APF7_MicroLabBox_update(void)
{
  /* Update for Memory: '<S9>/Memory' */
  Control_APF7_MicroLabBox_DW.Memory_PreviousInput =
    Control_APF7_MicroLabBox_B.Gain;

  /* Update for Memory: '<S9>/Memory1' */
  Control_APF7_MicroLabBox_DW.Memory1_PreviousInput =
    Control_APF7_MicroLabBox_B.Sum;

  /* Update for TransportDelay: '<S8>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = Control_APF7_MicroLabBox_M->Timing.t[0];
    Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head =
      ((Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head <
        (Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
       (Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head+1) : 0);
    if (Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head ==
        Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail) {
      Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail =
        ((Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail <
          (Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail+1) : 0);
    }

    (*tBuffer)[Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head] = simTime;
    (*uBuffer)[Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head] =
      Control_APF7_MicroLabBox_B.Output;
  }

  /* Update for TransportDelay: '<S8>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay1_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &Control_APF7_MicroLabBox_DW.TransportDelay1_PWORK.TUbufferPtrs[1];
    real_T simTime = Control_APF7_MicroLabBox_M->Timing.t[0];
    Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head =
      ((Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head <
        (Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.CircularBufSize-1)) ?
       (Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head+1) : 0);
    if (Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head ==
        Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Tail) {
      Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Tail =
        ((Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Tail <
          (Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.CircularBufSize-1))
         ? (Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Tail+1) : 0);
    }

    (*tBuffer)[Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head] = simTime;
    (*uBuffer)[Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head] =
      Control_APF7_MicroLabBox_B.Output;
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
  if (!(++Control_APF7_MicroLabBox_M->Timing.clockTick0)) {
    ++Control_APF7_MicroLabBox_M->Timing.clockTickH0;
  }

  Control_APF7_MicroLabBox_M->Timing.t[0] =
    Control_APF7_MicroLabBox_M->Timing.clockTick0 *
    Control_APF7_MicroLabBox_M->Timing.stepSize0 +
    Control_APF7_MicroLabBox_M->Timing.clockTickH0 *
    Control_APF7_MicroLabBox_M->Timing.stepSize0 * 4294967296.0;

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
    Control_APF7_MicroLabBox_M->Timing.clockTick1++;
    if (!Control_APF7_MicroLabBox_M->Timing.clockTick1) {
      Control_APF7_MicroLabBox_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void Control_APF7_MicroLabBox_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Control_APF7_MicroLabBox_M, 0,
                sizeof(RT_MODEL_Control_APF7_MicroLa_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Control_APF7_MicroLabBox_M->solverInfo,
                          &Control_APF7_MicroLabBox_M->Timing.simTimeStep);
    rtsiSetTPtr(&Control_APF7_MicroLabBox_M->solverInfo, &rtmGetTPtr
                (Control_APF7_MicroLabBox_M));
    rtsiSetStepSizePtr(&Control_APF7_MicroLabBox_M->solverInfo,
                       &Control_APF7_MicroLabBox_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Control_APF7_MicroLabBox_M->solverInfo,
                          (&rtmGetErrorStatus(Control_APF7_MicroLabBox_M)));
    rtsiSetRTModelPtr(&Control_APF7_MicroLabBox_M->solverInfo,
                      Control_APF7_MicroLabBox_M);
  }

  rtsiSetSimTimeStep(&Control_APF7_MicroLabBox_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&Control_APF7_MicroLabBox_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Control_APF7_MicroLabBox_M,
             &Control_APF7_MicroLabBox_M->Timing.tArray[0]);
  Control_APF7_MicroLabBox_M->Timing.stepSize0 = 1.0E-6;

  /* block I/O */
  (void) memset(((void *) &Control_APF7_MicroLabBox_B), 0,
                sizeof(B_Control_APF7_MicroLabBox_T));

  /* states (dwork) */
  (void) memset((void *)&Control_APF7_MicroLabBox_DW, 0,
                sizeof(DW_Control_APF7_MicroLabBox_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Control_APF7_MicroLabBox_InitializeDataMapInfo();

  {
    /* user code (registration function declaration) */
    /*Initialize global TRC pointers. */
    Control_APF7_MicroLabBox_rti_init_trc_pointers();
  }

  /* Start for TransportDelay: '<S8>/Transport Delay' */
  {
    real_T *pBuffer =
      &Control_APF7_MicroLabBox_DW.TransportDelay_RWORK.TUbufferArea[0];
    Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail = 0;
    Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Head = 0;
    Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Last = 0;
    Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = Control_APF7_MicroLabBox_P.TransportDelay_InitOutput;
    pBuffer[1024] = Control_APF7_MicroLabBox_M->Timing.t[0];
    Control_APF7_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    Control_APF7_MicroLabBox_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* Start for TransportDelay: '<S8>/Transport Delay1' */
  {
    real_T *pBuffer =
      &Control_APF7_MicroLabBox_DW.TransportDelay1_RWORK.TUbufferArea[0];
    Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Tail = 0;
    Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Head = 0;
    Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.Last = 0;
    Control_APF7_MicroLabBox_DW.TransportDelay1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = Control_APF7_MicroLabBox_P.TransportDelay1_InitOutput;
    pBuffer[1024] = Control_APF7_MicroLabBox_M->Timing.t[0];
    Control_APF7_MicroLabBox_DW.TransportDelay1_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    Control_APF7_MicroLabBox_DW.TransportDelay1_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* InitializeConditions for Memory: '<S9>/Memory' */
  Control_APF7_MicroLabBox_DW.Memory_PreviousInput =
    Control_APF7_MicroLabBox_P.Memory_InitialCondition;

  /* InitializeConditions for Memory: '<S9>/Memory1' */
  Control_APF7_MicroLabBox_DW.Memory1_PreviousInput =
    Control_APF7_MicroLabBox_P.Memory1_InitialCondition;
}

/* Model terminate function */
void Control_APF7_MicroLabBox_terminate(void)
{
  /* Terminate for S-Function (rti_commonblock): '<S52>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 11 --- */

  /* disable digital output channel 11-11 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_11,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_11);

  /* Terminate for S-Function (rti_commonblock): '<S53>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF1 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 12 --- */

  /* disable digital output channel 12-12 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_12,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_12);

  /* Terminate for S-Function (rti_commonblock): '<S54>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF10 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 15 --- */

  /* disable digital output channel 15-15 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_15,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_15);

  /* Terminate for S-Function (rti_commonblock): '<S55>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF7 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 13 --- */

  /* disable digital output channel 13-13 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_13,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_13);

  /* Terminate for S-Function (rti_commonblock): '<S56>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF8 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 14 --- */

  /* disable digital output channel 14-14 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_14,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_14);

  /* Terminate for S-Function (rti_commonblock): '<S57>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF9 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 16 --- */

  /* disable digital output channel 16-16 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_16,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_16);

  /* Terminate for S-Function (rti_commonblock): '<S58>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF10 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 7 --- */

  /* disable digital output channel 7-7 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_7,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_7);

  /* Terminate for S-Function (rti_commonblock): '<S59>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF2 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 2 --- */

  /* disable digital output channel 2-2 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_2,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_2);

  /* Terminate for S-Function (rti_commonblock): '<S60>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF3 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 3 --- */

  /* disable digital output channel 3-3 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_3,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_3);

  /* Terminate for S-Function (rti_commonblock): '<S61>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF7 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 4 --- */

  /* disable digital output channel 4-4 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_4,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_4);

  /* Terminate for S-Function (rti_commonblock): '<S62>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF8 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 5 --- */

  /* disable digital output channel 5-5 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_5,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_5);

  /* Terminate for S-Function (rti_commonblock): '<S63>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF9 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 6 --- */

  /* disable digital output channel 6-6 on port 1 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_6,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_6);

  /* Terminate for S-Function (rti_commonblock): '<S64>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF10 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 8 --- */

  /* disable digital output channel 8-8 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_8,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_8);

  /* Terminate for S-Function (rti_commonblock): '<S65>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF4 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 2 --- */

  /* disable digital output channel 2-2 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_2,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_2);

  /* Terminate for S-Function (rti_commonblock): '<S66>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF6 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 4 --- */

  /* disable digital output channel 4-4 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_4,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_4);

  /* Terminate for S-Function (rti_commonblock): '<S67>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF7 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 5 --- */

  /* disable digital output channel 5-5 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_5,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_5);

  /* Terminate for S-Function (rti_commonblock): '<S68>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF8 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 6 --- */

  /* disable digital output channel 6-6 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_6,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_6);

  /* Terminate for S-Function (rti_commonblock): '<S69>/S-Function1' */

  /* --- Control_APF7_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF9 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 7 --- */

  /* disable digital output channel 7-7 on port 2 *
   * (set to high-impedance), when the simulation terminates       */
  DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_7,
    DIO_CLASS1_HIGH_Z_ON);
  DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_7);

  /* Terminate for S-Function (rti_commonblock): '<S3>/S-Function1' incorporates:
   *  Constant: '<Root>/Duty Cycle'
   *  Constant: '<Root>/Period'
   */

  /* --- Control_APF7_MicroLabBox/DIO_CLASS1_PWM_BL1 --- */
  /* --- [RTI120X, PWM OUT] - Port: 3 - Channel: 1 --- */

  /* disable digital output channel 1 on port 3 *
   * (set to high-impedance), when the simulation terminates */
  DioCl1PwmOut_setOutputHighZ(pRTIDioC1PwmOut_Port_3_Ch_1, DIO_CLASS1_HIGH_Z_ON);
  DioCl1PwmOut_write(pRTIDioC1PwmOut_Port_3_Ch_1);
}
