/*
 * Control_APF7_MicroLabBox_data.c
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

#include "Control_APF7_MicroLabBox.h"
#include "Control_APF7_MicroLabBox_private.h"

/* Block parameters (default storage) */
P_Control_APF7_MicroLabBox_T Control_APF7_MicroLabBox_P = {
  /* Variable: Ganancia_Ica
   * Referenced by: '<S4>/Gain6'
   */
  26.804000000000002,

  /* Variable: Ganancia_Icb
   * Referenced by: '<S4>/Gain7'
   */
  27.956,

  /* Variable: Ganancia_Icc
   * Referenced by: '<S4>/Gain8'
   */
  27.659,

  /* Variable: Ganancia_Ila
   * Referenced by: '<S4>/Gain3'
   */
  27.659,

  /* Variable: Ganancia_Ilb
   * Referenced by: '<S4>/Gain4'
   */
  27.659,

  /* Variable: Ganancia_Ilc
   * Referenced by: '<S4>/Gain5'
   */
  27.083,

  /* Variable: Ganancia_Vsa
   * Referenced by: '<S4>/Gain'
   */
  250.0,

  /* Variable: Ganancia_Vsb
   * Referenced by: '<S4>/Gain10'
   */
  250.0,

  /* Variable: Ganancia_Vsc
   * Referenced by: '<S4>/Gain11'
   */
  250.0,

  /* Variable: Ica_offset
   * Referenced by: '<S4>/Constant6'
   */
  0.0,

  /* Variable: Icb_offset
   * Referenced by: '<S4>/Constant7'
   */
  0.0,

  /* Variable: Icc_offset
   * Referenced by: '<S4>/Constant8'
   */
  0.0,

  /* Variable: Ila_offset
   * Referenced by: '<S4>/Constant3'
   */
  0.0,

  /* Variable: Ilb_offset
   * Referenced by: '<S4>/Constant4'
   */
  0.0,

  /* Variable: Ilc_offset
   * Referenced by: '<S4>/Constant5'
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

  /* Variable: Ts
   * Referenced by:
   *   '<Root>/Period'
   *   '<S1>/Constant'
   *   '<S8>/Transport Delay'
   *   '<S8>/Transport Delay1'
   */
  4.0E-5,

  /* Variable: Vdc
   * Referenced by: '<S1>/Constant3'
   */
  65.0,

  /* Variable: Vsa_offset
   * Referenced by: '<S4>/Constant'
   */
  1.507,

  /* Variable: Vsb_offset
   * Referenced by: '<S4>/Constant1'
   */
  1.466,

  /* Variable: Vsc_offset
   * Referenced by: '<S4>/Constant2'
   */
  1.495,

  /* Variable: e
   * Referenced by: '<S1>/Constant8'
   */
  1.0,

  /* Variable: f
   * Referenced by: '<S1>/Constant10'
   */
  -1.9822289297925288,

  /* Variable: g
   * Referenced by: '<S1>/Constant9'
   */
  0.98238545061412552,

  /* Variable: ki
   * Referenced by: '<S1>/Constant5'
   */
  0.5,

  /* Variable: kp
   * Referenced by: '<S1>/Constant4'
   */
  0.005,

  /* Variable: lamda
   * Referenced by: '<S1>/Constant6'
   */
  0.5,

  /* Variable: sat
   * Referenced by: '<S1>/Constant13'
   */
  0.0,

  /* Variable: x
   * Referenced by: '<S1>/Constant11'
   */
  3.9130205399168227E-5,

  /* Variable: y
   * Referenced by: '<S1>/Constant12'
   */
  7.8260410798336455E-5,

  /* Variable: z
   * Referenced by: '<S1>/Constant7'
   */
  3.9130205399168227E-5,

  /* Mask Parameter: RepeatingSequence1_rep_seq_y
   * Referenced by: '<S45>/Look-Up Table1'
   */
  { -1.0, 1.0, -1.0 },

  /* Expression: 0
   * Referenced by: '<S9>/Constant1'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S9>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S9>/Memory'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S9>/Gain'
   */
  -1.0,

  /* Expression: 20
   * Referenced by: '<Root>/Constant'
   */
  20.0,

  /* Expression: 1
   * Referenced by: '<S9>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S9>/Memory1'
   */
  0.0,

  /* Expression: 10.0
   * Referenced by: '<S4>/Gain9'
   */
  10.0,

  /* Expression: 10.0
   * Referenced by: '<S4>/Gain1'
   */
  10.0,

  /* Expression: 10.0
   * Referenced by: '<S4>/Gain2'
   */
  10.0,

  /* Expression: -1
   * Referenced by: '<S4>/Gain12'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S4>/Gain13'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S4>/Gain14'
   */
  -1.0,

  /* Expression: 474.63
   * Referenced by: '<S4>/Gain15'
   */
  474.63,

  /* Expression: 474.63
   * Referenced by: '<S4>/Gain17'
   */
  474.63,

  /* Expression: 474.63
   * Referenced by: '<S4>/Gain18'
   */
  474.63,

  /* Expression: period
   * Referenced by: '<S45>/Constant'
   */
  4.0E-5,

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S45>/Look-Up Table1'
   */
  { 0.0, 2.0E-5, 4.0E-5 },

  /* Expression: -1
   * Referenced by: '<S36>/Gain1'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S8>/Transport Delay'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S37>/Gain1'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S8>/Transport Delay1'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S38>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S39>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S40>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S41>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S42>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S43>/Gain1'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S44>/Gain1'
   */
  -1.0,

  /* Expression: 0.5
   * Referenced by: '<Root>/Duty Cycle'
   */
  0.5
};
