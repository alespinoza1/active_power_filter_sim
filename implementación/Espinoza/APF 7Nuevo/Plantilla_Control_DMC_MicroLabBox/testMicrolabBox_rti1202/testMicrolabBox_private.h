/*
 * testMicrolabBox_private.h
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

#ifndef RTW_HEADER_testMicrolabBox_private_h_
#define RTW_HEADER_testMicrolabBox_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifdef __cplusplus

extern "C" {

#endif

  extern void duplicar_Start_wrapper(void);
  extern void duplicar_Outputs_wrapper(const real_T *u0,
    real_T *y0);
  extern void duplicar_Terminate_wrapper(void);

#ifdef __cplusplus

}
#endif

extern AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_2;
extern DacCl1AnalogOutSDrvObject *pRTIDacC1AnalogOut_Ch_2;
extern DacCl1AnalogOutSDrvObject *pRTIDacC1AnalogOut_Ch_1;
extern DioCl1DigInSDrvObject *pRTIDioC1DigIn_Port_2_Ch_16;
extern DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_3_Ch_1;

#endif                                 /* RTW_HEADER_testMicrolabBox_private_h_ */
