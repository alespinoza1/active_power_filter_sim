/*
 * smd_1202_sl_private.h
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

#ifndef RTW_HEADER_smd_1202_sl_private_h_
#define RTW_HEADER_smd_1202_sl_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* private model entry point functions */
extern void smd_1202_sl_derivatives(void);

#endif                                 /* RTW_HEADER_smd_1202_sl_private_h_ */
