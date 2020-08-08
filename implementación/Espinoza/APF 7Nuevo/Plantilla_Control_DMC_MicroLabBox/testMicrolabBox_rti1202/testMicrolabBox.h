/*
 * testMicrolabBox.h
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

#ifndef RTW_HEADER_testMicrolabBox_h_
#define RTW_HEADER_testMicrolabBox_h_
#include <string.h>
#include "rtw_modelmap.h"
#ifndef testMicrolabBox_COMMON_INCLUDES_
# define testMicrolabBox_COMMON_INCLUDES_
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* testMicrolabBox_COMMON_INCLUDES_ */

#include "testMicrolabBox_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
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
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T SFunction1;                   /* '<S1>/S-Function1' */
  real_T Saturation;                   /* '<Root>/Saturation' */
  real_T sal2;                         /* '<Root>/S-Function Builder' */
  real_T Saturation1;                  /* '<Root>/Saturation1' */
  boolean_T SFunction1_e;              /* '<S4>/S-Function1' */
} B_testMicrolabBox_T;

/* Parameters (default storage) */
struct P_testMicrolabBox_T_ {
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Gain1_Gain;                   /* Expression: 0.1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 10
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -0.5
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Gain2_Gain;                   /* Expression: 0.1
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 10
                                        * Referenced by: '<Root>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -0.5
                                        * Referenced by: '<Root>/Saturation1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_testMicrolabBox_T {
  const char_T *errorStatus;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_testMicrolabBox_T testMicrolabBox_P;

/* Block signals (default storage) */
extern B_testMicrolabBox_T testMicrolabBox_B;

/* Model entry point functions */
extern void testMicrolabBox_initialize(void);
extern void testMicrolabBox_output(void);
extern void testMicrolabBox_update(void);
extern void testMicrolabBox_terminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  testMicrolabBox_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_testMicrolabBox_T *const testMicrolabBox_M;

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
 * '<Root>' : 'testMicrolabBox'
 * '<S1>'   : 'testMicrolabBox/ADC_CLASS1_BL1'
 * '<S2>'   : 'testMicrolabBox/DAC_CLASS1_BL1'
 * '<S3>'   : 'testMicrolabBox/DAC_CLASS1_BL2'
 * '<S4>'   : 'testMicrolabBox/DIO_CLASS1_BIT_IN_BL1'
 * '<S5>'   : 'testMicrolabBox/DIO_CLASS1_BIT_OUT_BL1'
 * '<S6>'   : 'testMicrolabBox/RTI Data'
 * '<S7>'   : 'testMicrolabBox/RTI Data/RTI Data Store'
 * '<S8>'   : 'testMicrolabBox/RTI Data/RTI Data Store/RTI Data Store'
 * '<S9>'   : 'testMicrolabBox/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
 */
#endif                                 /* RTW_HEADER_testMicrolabBox_h_ */
