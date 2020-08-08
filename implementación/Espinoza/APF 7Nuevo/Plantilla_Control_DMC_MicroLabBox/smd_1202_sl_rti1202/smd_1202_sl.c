/*
 * smd_1202_sl.c
 *
 * Code generation for model "smd_1202_sl".
 *
 * Model version              : 1.31
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Sat Feb  9 12:10:58 2019
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "smd_1202_sl_trc_ptr.h"
#include "smd_1202_sl.h"
#include "smd_1202_sl_private.h"

/* Block signals (default storage) */
B_smd_1202_sl_T smd_1202_sl_B;

/* Continuous states */
X_smd_1202_sl_T smd_1202_sl_X;

/* Block states (default storage) */
DW_smd_1202_sl_T smd_1202_sl_DW;

/* Real-time model */
RT_MODEL_smd_1202_sl_T smd_1202_sl_M_;
RT_MODEL_smd_1202_sl_T *const smd_1202_sl_M = &smd_1202_sl_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  smd_1202_sl_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void smd_1202_sl_output(void)
{
  real_T Bias;
  if (rtmIsMajorTimeStep(smd_1202_sl_M)) {
    /* set solver stop time */
    if (!(smd_1202_sl_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&smd_1202_sl_M->solverInfo,
                            ((smd_1202_sl_M->Timing.clockTickH0 + 1) *
        smd_1202_sl_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&smd_1202_sl_M->solverInfo,
                            ((smd_1202_sl_M->Timing.clockTick0 + 1) *
        smd_1202_sl_M->Timing.stepSize0 + smd_1202_sl_M->Timing.clockTickH0 *
        smd_1202_sl_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(smd_1202_sl_M)) {
    smd_1202_sl_M->Timing.t[0] = rtsiGetT(&smd_1202_sl_M->solverInfo);
  }

  /* Integrator: '<Root>/Integrator 2' */
  smd_1202_sl_B.x = smd_1202_sl_X.Integrator2_CSTATE;
  if (rtmIsMajorTimeStep(smd_1202_sl_M)) {
  }

  /* SignalGenerator: '<Root>/x disp' */
  Bias = smd_1202_sl_P.xdisp_Frequency * smd_1202_sl_M->Timing.t[0];
  if (Bias - floor(Bias) >= 0.5) {
    smd_1202_sl_B.xdisp = smd_1202_sl_P.xdisp_Amplitude;
  } else {
    smd_1202_sl_B.xdisp = -smd_1202_sl_P.xdisp_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/x disp' */

  /* Sum: '<Root>/Sum' */
  smd_1202_sl_B.Sum = smd_1202_sl_B.x - smd_1202_sl_B.xdisp;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S2>/C'
   */
  smd_1202_sl_B.Product = smd_1202_sl_B.Sum * smd_1202_sl_P.ModelParameters_C;

  /* Integrator: '<Root>/Integrator 1' */
  smd_1202_sl_B.v = smd_1202_sl_X.Integrator1_CSTATE;

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S2>/d'
   */
  smd_1202_sl_B.Product1 = smd_1202_sl_B.v * smd_1202_sl_P.ModelParameters_d;

  /* Sum: '<S1>/Sum' */
  smd_1202_sl_B.Sum_e = (0.0 - smd_1202_sl_B.Product1) - smd_1202_sl_B.Product;

  /* Product: '<S1>/Product2' incorporates:
   *  Constant: '<S2>/m'
   */
  smd_1202_sl_B.Product2 = smd_1202_sl_B.Sum_e / smd_1202_sl_P.ModelParameters_m;
}

/* Model update function */
void smd_1202_sl_update(void)
{
  if (rtmIsMajorTimeStep(smd_1202_sl_M)) {
    rt_ertODEUpdateContinuousStates(&smd_1202_sl_M->solverInfo);
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
  if (!(++smd_1202_sl_M->Timing.clockTick0)) {
    ++smd_1202_sl_M->Timing.clockTickH0;
  }

  smd_1202_sl_M->Timing.t[0] = rtsiGetSolverStopTime(&smd_1202_sl_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.0001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    smd_1202_sl_M->Timing.clockTick1++;
    if (!smd_1202_sl_M->Timing.clockTick1) {
      smd_1202_sl_M->Timing.clockTickH1++;
    }
  }
}

/* Derivatives for root system: '<Root>' */
void smd_1202_sl_derivatives(void)
{
  XDot_smd_1202_sl_T *_rtXdot;
  _rtXdot = ((XDot_smd_1202_sl_T *) smd_1202_sl_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator 2' */
  _rtXdot->Integrator2_CSTATE = smd_1202_sl_B.v;

  /* Derivatives for Integrator: '<Root>/Integrator 1' */
  _rtXdot->Integrator1_CSTATE = smd_1202_sl_B.Product2;
}

/* Model initialize function */
void smd_1202_sl_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)smd_1202_sl_M, 0,
                sizeof(RT_MODEL_smd_1202_sl_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&smd_1202_sl_M->solverInfo,
                          &smd_1202_sl_M->Timing.simTimeStep);
    rtsiSetTPtr(&smd_1202_sl_M->solverInfo, &rtmGetTPtr(smd_1202_sl_M));
    rtsiSetStepSizePtr(&smd_1202_sl_M->solverInfo,
                       &smd_1202_sl_M->Timing.stepSize0);
    rtsiSetdXPtr(&smd_1202_sl_M->solverInfo, &smd_1202_sl_M->derivs);
    rtsiSetContStatesPtr(&smd_1202_sl_M->solverInfo, (real_T **)
                         &smd_1202_sl_M->contStates);
    rtsiSetNumContStatesPtr(&smd_1202_sl_M->solverInfo,
      &smd_1202_sl_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&smd_1202_sl_M->solverInfo,
      &smd_1202_sl_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&smd_1202_sl_M->solverInfo,
      &smd_1202_sl_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&smd_1202_sl_M->solverInfo,
      &smd_1202_sl_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&smd_1202_sl_M->solverInfo, (&rtmGetErrorStatus
      (smd_1202_sl_M)));
    rtsiSetRTModelPtr(&smd_1202_sl_M->solverInfo, smd_1202_sl_M);
  }

  rtsiSetSimTimeStep(&smd_1202_sl_M->solverInfo, MAJOR_TIME_STEP);
  smd_1202_sl_M->intgData.f[0] = smd_1202_sl_M->odeF[0];
  smd_1202_sl_M->contStates = ((X_smd_1202_sl_T *) &smd_1202_sl_X);
  rtsiSetSolverData(&smd_1202_sl_M->solverInfo, (void *)&smd_1202_sl_M->intgData);
  rtsiSetSolverName(&smd_1202_sl_M->solverInfo,"ode1");
  rtmSetTPtr(smd_1202_sl_M, &smd_1202_sl_M->Timing.tArray[0]);
  smd_1202_sl_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  {
    smd_1202_sl_B.x = 0.0;
    smd_1202_sl_B.xdisp = 0.0;
    smd_1202_sl_B.Sum = 0.0;
    smd_1202_sl_B.Product = 0.0;
    smd_1202_sl_B.v = 0.0;
    smd_1202_sl_B.Product1 = 0.0;
    smd_1202_sl_B.Sum_e = 0.0;
    smd_1202_sl_B.Product2 = 0.0;
  }

  /* states (continuous) */
  {
    (void) memset((void *)&smd_1202_sl_X, 0,
                  sizeof(X_smd_1202_sl_T));
  }

  /* states (dwork) */
  (void) memset((void *)&smd_1202_sl_DW, 0,
                sizeof(DW_smd_1202_sl_T));

  {
    /* user code (registration function declaration) */
    /*Initialize global TRC pointers. */
    smd_1202_sl_rti_init_trc_pointers();
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator 2' */
  smd_1202_sl_X.Integrator2_CSTATE = smd_1202_sl_P.Integrator2_IC;

  /* InitializeConditions for Integrator: '<Root>/Integrator 1' */
  smd_1202_sl_X.Integrator1_CSTATE = smd_1202_sl_P.Integrator1_IC;
}

/* Model terminate function */
void smd_1202_sl_terminate(void)
{
  /* (no terminate code required) */
}
