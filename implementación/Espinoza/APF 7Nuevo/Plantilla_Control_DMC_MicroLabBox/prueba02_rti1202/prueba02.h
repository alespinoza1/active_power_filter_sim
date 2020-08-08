/*
 * prueba02.h
 *
 * Code generation for model "prueba02".
 *
 * Model version              : 1.40
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Tue Apr 16 18:12:31 2019
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_prueba02_h_
#define RTW_HEADER_prueba02_h_
#include <string.h>
#include "rtw_modelmap.h"
#ifndef prueba02_COMMON_INCLUDES_
# define prueba02_COMMON_INCLUDES_
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* prueba02_COMMON_INCLUDES_ */

#include "prueba02_types.h"

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

/* Parameters (default storage) */
struct P_prueba02_T_ {
  real_T Constant_Value;               /* Expression: 0.02
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_prueba02_T {
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
extern P_prueba02_T prueba02_P;

/* Model entry point functions */
extern void prueba02_initialize(void);
extern void prueba02_output(void);
extern void prueba02_update(void);
extern void prueba02_terminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  prueba02_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_prueba02_T *const prueba02_M;

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
 * '<Root>' : 'prueba02'
 * '<S1>'   : 'prueba02/DAC_CLASS1_BL1'
 * '<S2>'   : 'prueba02/RTI Data'
 * '<S3>'   : 'prueba02/RTI Data/RTI Data Store'
 * '<S4>'   : 'prueba02/RTI Data/RTI Data Store/RTI Data Store'
 * '<S5>'   : 'prueba02/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
 */
#endif                                 /* RTW_HEADER_prueba02_h_ */
