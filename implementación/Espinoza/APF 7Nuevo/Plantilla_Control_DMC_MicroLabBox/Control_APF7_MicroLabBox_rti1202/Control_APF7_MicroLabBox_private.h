/*
 * Control_APF7_MicroLabBox_private.h
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

#ifndef RTW_HEADER_Control_APF7_MicroLabBox_private_h_
#define RTW_HEADER_Control_APF7_MicroLabBox_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "Control_APF7_MicroLabBox.h"

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

#ifdef __cplusplus

extern "C" {

#endif

  extern void Control_APF7_algoritmo_Start_wrapper(void);
  extern void Control_APF7_algoritmo_Outputs_wrapper(const real_T *in,
    real_T *SwA,
    real_T *io,
    real_T *SwC,
    real_T *fc,
    real_T *Vs_alfabeta,
    real_T *PLQL,
    real_T *QCQS,
    real_T *ic_km1,
    real_T *Icref,
    real_T *Varfiltro);
  extern void Control_APF7_algoritmo_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void seguidor_2S_Start_wrapper(void);
  extern void seguidor_2S_Outputs_wrapper(const real_T *u0,
    real_T *y0);
  extern void seguidor_2S_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void seguidor3_Start_wrapper(void);
  extern void seguidor3_Outputs_wrapper(const real_T *u0,
    real_T *y0);
  extern void seguidor3_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void seguidor12_Start_wrapper(void);
  extern void seguidor12_Outputs_wrapper(const real_T *u0,
    real_T *y0);
  extern void seguidor12_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void seguidor4_Start_wrapper(void);
  extern void seguidor4_Outputs_wrapper(const real_T *u0,
    real_T *y0);
  extern void seguidor4_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void seguidor_Start_wrapper(void);
  extern void seguidor_Outputs_wrapper(const real_T *u0,
    real_T *y0);
  extern void seguidor_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_1;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_2;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_3;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_9;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_10;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_11;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_17;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_18;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_19;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_4;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_5;
extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_6;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_11;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_12;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_15;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_13;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_14;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_16;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_7;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_2;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_3;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_4;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_5;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_6;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_8;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_2;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_4;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_5;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_6;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_7;
extern DioCl1PwmOutSDrvObject *pRTIDioC1PwmOut_Port_3_Ch_1;
extern real_T rt_remd_snf(real_T u0, real_T u1);
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
  ;
extern real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
extern void Control_APF7_MicroLab_SubSystem(void);

#endif                                 /* RTW_HEADER_Control_APF7_MicroLabBox_private_h_ */
