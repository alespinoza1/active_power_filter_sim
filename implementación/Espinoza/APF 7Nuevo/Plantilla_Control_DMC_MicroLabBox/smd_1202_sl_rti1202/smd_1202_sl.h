/*
 * smd_1202_sl.h
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

#ifndef RTW_HEADER_smd_1202_sl_h_
#define RTW_HEADER_smd_1202_sl_h_
#include <math.h>
#include <string.h>
#ifndef smd_1202_sl_COMMON_INCLUDES_
# define smd_1202_sl_COMMON_INCLUDES_
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* smd_1202_sl_COMMON_INCLUDES_ */

#include "smd_1202_sl_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T x;                            /* '<Root>/Integrator 2' */
  real_T xdisp;                        /* '<Root>/x disp' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T Product;                      /* '<S1>/Product' */
  real_T v;                            /* '<Root>/Integrator 1' */
  real_T Product1;                     /* '<S1>/Product1' */
  real_T Sum_e;                        /* '<S1>/Sum' */
  real_T Product2;                     /* '<S1>/Product2' */
} B_smd_1202_sl_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData;
  } x_PWORK;                           /* '<Root>/x' */
} DW_smd_1202_sl_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator2_CSTATE;           /* '<Root>/Integrator 2' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator 1' */
} X_smd_1202_sl_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator2_CSTATE;           /* '<Root>/Integrator 2' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator 1' */
} XDot_smd_1202_sl_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator2_CSTATE;        /* '<Root>/Integrator 2' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator 1' */
} XDis_smd_1202_sl_T;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* Parameters (default storage) */
struct P_smd_1202_sl_T_ {
  real_T ModelParameters_C;            /* Mask Parameter: ModelParameters_C
                                        * Referenced by: '<S2>/C'
                                        */
  real_T ModelParameters_d;            /* Mask Parameter: ModelParameters_d
                                        * Referenced by: '<S2>/d'
                                        */
  real_T ModelParameters_m;            /* Mask Parameter: ModelParameters_m
                                        * Referenced by: '<S2>/m'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * Referenced by: '<Root>/Integrator 2'
                                        */
  real_T xdisp_Amplitude;              /* Expression: 0.5
                                        * Referenced by: '<Root>/x disp'
                                        */
  real_T xdisp_Frequency;              /* Expression: 50
                                        * Referenced by: '<Root>/x disp'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<Root>/Integrator 1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_smd_1202_sl_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_smd_1202_sl_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][2];
  ODE1_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_smd_1202_sl_T smd_1202_sl_P;

/* Block signals (default storage) */
extern B_smd_1202_sl_T smd_1202_sl_B;

/* Continuous states (default storage) */
extern X_smd_1202_sl_T smd_1202_sl_X;

/* Block states (default storage) */
extern DW_smd_1202_sl_T smd_1202_sl_DW;

/* Model entry point functions */
extern void smd_1202_sl_initialize(void);
extern void smd_1202_sl_output(void);
extern void smd_1202_sl_update(void);
extern void smd_1202_sl_terminate(void);

/* Real-time Model object */
extern RT_MODEL_smd_1202_sl_T *const smd_1202_sl_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'smd_1202_sl'
 * '<S1>'   : 'smd_1202_sl/Equation Block'
 * '<S2>'   : 'smd_1202_sl/Model Parameters'
 * '<S3>'   : 'smd_1202_sl/RTI Data'
 * '<S4>'   : 'smd_1202_sl/RTI Data/RTI Data Store'
 * '<S5>'   : 'smd_1202_sl/RTI Data/RTI Data Store/RTI Data Store'
 * '<S6>'   : 'smd_1202_sl/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
 */
#endif                                 /* RTW_HEADER_smd_1202_sl_h_ */
