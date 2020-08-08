/*
 * Control_DMC_MicroLabBox_data.c
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

#include "Control_DMC_MicroLabBox.h"
#include "Control_DMC_MicroLabBox_private.h"

/* Block parameters (default storage) */
P_Control_DMC_MicroLabBox_T Control_DMC_MicroLabBox_P = {
  /* Variable: Ganancia_Ica
   * Referenced by: '<S6>/Gain6'
   */
  26.804000000000002,

  /* Variable: Ganancia_Icb
   * Referenced by: '<S6>/Gain7'
   */
  27.956,

  /* Variable: Ganancia_Icc
   * Referenced by: '<S6>/Gain8'
   */
  27.659,

  /* Variable: Ganancia_Ila
   * Referenced by: '<S6>/Gain3'
   */
  27.659,

  /* Variable: Ganancia_Ilb
   * Referenced by: '<S6>/Gain4'
   */
  27.659,

  /* Variable: Ganancia_Ilc
   * Referenced by: '<S6>/Gain5'
   */
  27.083,

  /* Variable: Ganancia_Vsa
   * Referenced by: '<S6>/Gain'
   */
  361.4,

  /* Variable: Ganancia_Vsb
   * Referenced by: '<S6>/Gain1'
   */
  355.0,

  /* Variable: Ganancia_Vsc
   * Referenced by: '<S6>/Gain2'
   */
  350.0,

  /* Variable: Ica_offset
   * Referenced by: '<S6>/Constant6'
   */
  0.0,

  /* Variable: Icb_offset
   * Referenced by: '<S6>/Constant7'
   */
  0.0,

  /* Variable: Icc_offset
   * Referenced by: '<S6>/Constant8'
   */
  0.0,

  /* Variable: Ila_offset
   * Referenced by: '<S6>/Constant3'
   */
  0.0,

  /* Variable: Ilb_offset
   * Referenced by: '<S6>/Constant4'
   */
  0.0,

  /* Variable: Ilc_offset
   * Referenced by: '<S6>/Constant5'
   */
  0.0,

  /* Variable: Lc
   * Referenced by: '<S1>/Constant2'
   */
  0.01,

  /* Variable: Rc
   * Referenced by: '<S1>/Constant1'
   */
  0.35,

  /* Variable: Tm
   * Referenced by: '<S1>/Transport Delay'
   */
  1.0E-6,

  /* Variable: Ts
   * Referenced by:
   *   '<Root>/Period'
   *   '<S1>/Constant'
   */
  2.5E-5,

  /* Variable: Vdc
   * Referenced by: '<S1>/Constant3'
   */
  180.0,

  /* Variable: Vsa_offset
   * Referenced by: '<S6>/Constant'
   */
  0.0,

  /* Variable: Vsb_offset
   * Referenced by: '<S6>/Constant1'
   */
  0.0,

  /* Variable: Vsc_offset
   * Referenced by: '<S6>/Constant2'
   */
  0.0,

  /* Variable: vect
   * Referenced by: '<S1>/Constant4'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S19>/Constant1'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S19>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S19>/Memory'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S19>/Gain'
   */
  -1.0,

  /* Expression: 20
   * Referenced by: '<Root>/Constant'
   */
  20.0,

  /* Expression: 1
   * Referenced by: '<S19>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S19>/Memory1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Transport Delay'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<Root>/Duty Cycle'
   */
  0.5
};
