/*
 * prueba.h
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

#ifndef RTW_HEADER_prueba_h_
#define RTW_HEADER_prueba_h_
#include <string.h>
#ifndef prueba_COMMON_INCLUDES_
# define prueba_COMMON_INCLUDES_
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* prueba_COMMON_INCLUDES_ */

#include "prueba_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
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
} B_prueba_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData;
  } TimeScope_PWORK;                   /* '<Root>/Time Scope' */
} DW_prueba_T;

/* Real-time Model Data Structure */
struct tag_RTM_prueba_T {
  const char_T *errorStatus;

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

/* Block signals (default storage) */
extern B_prueba_T prueba_B;

/* Block states (default storage) */
extern DW_prueba_T prueba_DW;

/* Model entry point functions */
extern void prueba_initialize(void);
extern void prueba_output(void);
extern void prueba_update(void);
extern void prueba_terminate(void);

/* Real-time Model object */
extern RT_MODEL_prueba_T *const prueba_M;

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
 * '<Root>' : 'prueba'
 * '<S1>'   : 'prueba/ADC_CLASS1_BL1'
 * '<S2>'   : 'prueba/RTI Data'
 * '<S3>'   : 'prueba/RTI Data/RTI Data Store'
 * '<S4>'   : 'prueba/RTI Data/RTI Data Store/RTI Data Store'
 * '<S5>'   : 'prueba/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
 */
#endif                                 /* RTW_HEADER_prueba_h_ */
