#include "__cf_control_filtro_dq_mod21.h"
#ifndef RTW_HEADER_control_filtro_dq_mod21_acc_h_
#define RTW_HEADER_control_filtro_dq_mod21_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef control_filtro_dq_mod21_acc_COMMON_INCLUDES_
#define control_filtro_dq_mod21_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "control_filtro_dq_mod21_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_11_0_0 [ 64 ] ; real_T B_11_1_0 ; real_T B_11_2_0 ;
real_T B_11_3_0 ; real_T B_11_4_0 ; real_T B_11_5_0 ; real_T B_11_6_0 ;
real_T B_11_7_0 ; real_T B_11_8_0 ; real_T B_11_9_0 ; real_T B_11_10_0 ;
real_T B_11_11_0 ; real_T B_11_12_0 ; real_T B_11_13_0 [ 98 ] ; real_T
B_11_13_1 [ 64 ] ; real_T B_11_34_0 ; real_T B_11_39_0 ; real_T B_11_41_0 ;
real_T B_11_43_0 ; real_T B_11_44_0 ; real_T B_11_48_0 [ 3 ] ; real_T
B_11_49_0 ; real_T B_11_52_0 ; real_T B_11_53_0 ; real_T B_11_57_0 [ 3 ] ;
real_T B_11_58_0 ; real_T B_11_62_0 ; real_T B_11_63_0 ; real_T B_11_64_0 ;
real_T B_11_67_0 ; real_T B_11_69_0 ; real_T B_11_73_0 ; real_T B_11_80_0 [ 3
] ; real_T B_11_84_0 [ 3 ] ; real_T B_11_88_0 [ 3 ] ; real_T B_11_89_0 [ 3 ]
; real_T B_11_90_0 ; real_T B_11_92_0 ; real_T B_11_94_0 ; real_T B_11_103_0
; real_T B_11_105_0 ; real_T B_11_118_0 ; real_T B_11_120_0 ; real_T
B_11_129_0 ; real_T B_11_131_0 ; real_T B_11_144_0 ; real_T B_11_146_0 ;
real_T B_11_155_0 ; real_T B_11_157_0 ; real_T B_11_168_0 ; real_T B_11_170_0
; real_T B_11_186_0 ; real_T B_11_188_0 ; real_T B_11_192_0 ; real_T
B_11_205_0 ; real_T B_11_207_0 ; real_T B_11_211_0 ; real_T B_11_227_0 ;
real_T B_11_229_0 ; real_T B_11_234_0 ; real_T B_11_236_0 ; real_T B_11_245_0
; real_T B_11_247_0 ; real_T B_11_260_0 ; real_T B_11_262_0 ; real_T
B_11_271_0 ; real_T B_11_273_0 ; real_T B_11_286_0 ; real_T B_11_288_0 ;
real_T B_11_297_0 ; real_T B_11_299_0 ; real_T B_11_310_0 ; real_T B_11_312_0
; real_T B_11_316_0 ; real_T B_11_329_0 ; real_T B_11_331_0 ; real_T
B_11_335_0 ; real_T B_11_348_0 ; real_T B_11_350_0 ; real_T B_11_354_0 ;
real_T B_11_370_0 ; real_T B_11_372_0 ; real_T B_11_377_0 ; real_T B_11_379_0
; real_T B_11_388_0 ; real_T B_11_390_0 ; real_T B_11_403_0 ; real_T
B_11_405_0 ; real_T B_11_414_0 ; real_T B_11_416_0 ; real_T B_11_429_0 ;
real_T B_11_431_0 ; real_T B_11_440_0 ; real_T B_11_442_0 ; real_T B_11_453_0
; real_T B_11_455_0 ; real_T B_11_459_0 ; real_T B_11_472_0 ; real_T
B_11_474_0 ; real_T B_11_478_0 ; real_T B_11_491_0 ; real_T B_11_493_0 ;
real_T B_11_497_0 ; real_T B_11_517_0 [ 3 ] ; real_T B_11_518_0 ; real_T
B_11_528_0 [ 6 ] ; real_T B_11_529_0 ; real_T B_11_530_0 [ 6 ] ; real_T
B_11_537_0 [ 6 ] ; real_T B_11_634_0 ; real_T B_11_635_0 ; real_T B_11_638_0
; real_T B_11_640_0 ; real_T B_11_641_0 ; real_T B_11_644_0 ; real_T
B_11_646_0 ; real_T B_11_647_0 ; real_T B_11_650_0 ; real_T B_11_652_0 ;
real_T B_11_653_0 ; real_T B_11_656_0 ; real_T B_11_658_0 ; real_T B_11_659_0
; real_T B_11_662_0 ; real_T B_11_664_0 ; real_T B_11_665_0 ; real_T
B_11_668_0 ; real_T B_11_669_0 ; real_T B_11_674_0 ; real_T B_11_675_0 ;
real_T B_11_677_0 ; real_T B_11_681_0 ; real_T B_11_682_0 ; real_T B_11_686_0
; real_T B_11_687_0 ; real_T B_11_691_0 ; real_T B_11_692_0 ; real_T
B_11_742_0 ; real_T B_11_753_0 ; real_T B_11_754_0 ; real_T B_11_755_0 ;
real_T B_11_756_0 ; real_T B_11_757_0 ; real_T B_11_758_0 ; real_T B_11_760_0
; real_T B_11_764_0 ; real_T B_11_766_0 ; real_T B_11_769_0 ; real_T
B_11_771_0 ; real_T B_11_774_0 ; real_T B_11_781_0 ; real_T B_10_1_0 [ 6 ] ;
real_T B_10_2_0 [ 6 ] ; real_T B_10_3_0 ; real_T B_10_4_0 [ 6 ] ; real_T
B_10_10_0 [ 6 ] ; real_T B_10_12_0 [ 6 ] ; real_T B_8_1_0 [ 6 ] ; real_T
B_8_2_0 [ 6 ] ; real_T B_8_3_0 ; real_T B_8_4_0 [ 6 ] ; real_T B_8_11_0 [ 6 ]
; real_T B_8_13_0 [ 6 ] ; real_T B_8_14_0 [ 6 ] ; real_T B_8_15_0 ; real_T
B_8_16_0 [ 6 ] ; real_T B_8_23_0 [ 6 ] ; real_T B_8_26_0 [ 6 ] ; real_T
B_5_1_0 [ 6 ] ; real_T B_5_2_0 [ 6 ] ; real_T B_5_3_0 ; real_T B_5_4_0 [ 6 ]
; real_T B_5_10_0 [ 6 ] ; real_T B_5_12_0 [ 6 ] ; real_T B_3_1_0 [ 6 ] ;
real_T B_3_2_0 [ 6 ] ; real_T B_3_3_0 ; real_T B_3_4_0 [ 6 ] ; real_T
B_3_11_0 [ 6 ] ; real_T B_3_13_0 [ 6 ] ; real_T B_3_14_0 [ 6 ] ; real_T
B_3_15_0 ; real_T B_3_16_0 [ 6 ] ; real_T B_3_23_0 [ 6 ] ; real_T B_3_26_0 [
6 ] ; real_T B_11_551_0 [ 6 ] ; real_T B_11_557_0 [ 3 ] ; boolean_T B_11_50_0
; boolean_T B_11_522_0 ; boolean_T B_11_524_0 ; boolean_T B_11_540_0 ;
boolean_T B_11_542_0 ; char_T pad_B_11_542_0 [ 3 ] ; }
B_control_filtro_dq_mod21_T ; typedef struct { real_T StateSpace_DSTATE [ 57
] ; real_T Integrator_DSTATE ; real_T Integrator_DSTATE_l ; real_T
Integ4_DSTATE [ 6 ] ; real_T UnitDelay_DSTATE [ 6 ] ; real_T
UnitDelay1_DSTATE [ 6 ] ; real_T Integrator_DSTATE_j ; real_T Integ4_DSTATE_h
[ 6 ] ; real_T UnitDelay_DSTATE_a [ 6 ] ; real_T UnitDelay1_DSTATE_g [ 6 ] ;
real_T Integ4_DSTATE_b [ 6 ] ; real_T UnitDelay_DSTATE_k [ 6 ] ; real_T
UnitDelay1_DSTATE_i [ 6 ] ; real_T Integ4_DSTATE_o [ 6 ] ; real_T
UnitDelay_DSTATE_c [ 6 ] ; real_T UnitDelay1_DSTATE_ip [ 6 ] ; real_T
Integ4_DSTATE_m [ 6 ] ; real_T UnitDelay_DSTATE_p [ 6 ] ; real_T
UnitDelay1_DSTATE_l [ 6 ] ; real_T Integ4_DSTATE_h0 [ 6 ] ; real_T
UnitDelay_DSTATE_pe [ 6 ] ; real_T UnitDelay1_DSTATE_n [ 6 ] ; real_T
Integ4_DSTATE_l [ 6 ] ; real_T UnitDelay_DSTATE_o [ 6 ] ; real_T
UnitDelay1_DSTATE_ib [ 6 ] ; real_T lastSin ; real_T lastCos ; real_T
lastSin_a ; real_T lastCos_j ; real_T lastSin_o ; real_T lastCos_b ; real_T
lastSin_k ; real_T lastCos_f ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay_RWORK_e
; struct { real_T modelTStart ; } TransportDelay_RWORK_g ; struct { real_T
modelTStart ; } TransportDelay_RWORK_h ; struct { real_T modelTStart ; }
TransportDelay_RWORK_ed ; struct { real_T modelTStart ; }
TransportDelay_RWORK_k ; real_T SFunction_RWORK ; struct { real_T modelTStart
; } T_RWORK ; struct { real_T modelTStart ; } TransportDelay_RWORK_l ; struct
{ real_T modelTStart ; } TransportDelay_RWORK_m ; real_T SFunction_RWORK_a ;
real_T SFunction_RWORK_p ; real_T SFunction_RWORK_k ; real_T
SFunction_RWORK_f ; real_T SFunction_RWORK_fk ; real_T SFunction_RWORK_o ;
struct { void * AS ; void * BS ; void * CS ; void * DS ; void * DX_COL ; void
* BD_COL ; void * TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ;
void * SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ;
void * XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG
; void * Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } StateSpace_PWORK ; struct {
void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_n ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay_PWORK_f ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_l ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_i ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_c ; void * Scope_PWORK [ 4 ] ; void * Scope1_PWORK ;
void * SFunction_PWORK [ 6 ] ; void * Scope2_PWORK ; void * Scope4_PWORK ;
void * Scope5_PWORK ; void * Scope1_PWORK_i ; void * Scope16_PWORK ; void *
Scope_PWORK_p ; void * Scope3_PWORK ; void * Scope_PWORK_i ; struct { void *
TUbufferPtrs [ 2 ] ; } T_PWORK ; void * Scope1_PWORK_p ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_j ; void * Scope2_PWORK_c ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_a ; void *
Scope3_PWORK_l ; void * ToWorkspace_PWORK ; void * SFunction_PWORK_a [ 6 ] ;
void * SFunction_PWORK_a0 [ 6 ] ; void * SFunction_PWORK_n [ 6 ] ; void *
SFunction_PWORK_nz [ 6 ] ; void * SFunction_PWORK_m [ 6 ] ; void *
SFunction_PWORK_f [ 6 ] ; int32_T TrueRMS_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T RMS_sysIdxToRun ;
int32_T systemEnable ; int32_T systemEnable_p ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_ey ; int32_T TrueRMS_sysIdxToRun_l
; int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_g ; int32_T
RMS_sysIdxToRun_g ; int32_T systemEnable_g ; int32_T systemEnable_h ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_d ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_gp ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_l ; int_T StateSpace_IWORK [ 11 ]
; struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ;
int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_o ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_e ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_p ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_b ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_os ;
int_T SFunction_IWORK [ 6 ] ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } T_IWORK ; struct { int_T Tail
; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_h ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_ej ;
int_T SFunction_IWORK_g [ 6 ] ; int_T SFunction_IWORK_j [ 6 ] ; int_T
SFunction_IWORK_d [ 6 ] ; int_T SFunction_IWORK_c [ 6 ] ; int_T
SFunction_IWORK_o [ 6 ] ; int_T SFunction_IWORK_ct [ 6 ] ; int8_T
Integrator_PrevResetState ; int8_T TrueRMS_SubsysRanBC ; int8_T
RMS_SubsysRanBC ; int8_T TrueRMS_SubsysRanBC_i ; int8_T RMS_SubsysRanBC_f ;
uint8_T Integ4_SYSTEM_ENABLE ; uint8_T Integ4_NumInitCond ; uint8_T
Integ4_SYSTEM_ENABLE_n ; uint8_T Integ4_NumInitCond_l ; uint8_T
Integ4_SYSTEM_ENABLE_l ; uint8_T Integ4_NumInitCond_k ; uint8_T
Integ4_SYSTEM_ENABLE_b ; uint8_T Integ4_NumInitCond_a ; uint8_T
Integ4_SYSTEM_ENABLE_a ; uint8_T Integ4_NumInitCond_o ; uint8_T
Integ4_SYSTEM_ENABLE_k ; uint8_T Integ4_NumInitCond_km ; uint8_T
Integ4_SYSTEM_ENABLE_g ; uint8_T Integ4_NumInitCond_af ; boolean_T
Initial_FirstOutputTime ; boolean_T TrueRMS_MODE ; boolean_T RMS_MODE ;
boolean_T TrueRMS_MODE_c ; boolean_T RMS_MODE_i ; char_T pad_RMS_MODE_i [ 4 ]
; } DW_control_filtro_dq_mod21_T ; typedef struct { real_T Integrator1_CSTATE
; real_T Integrator1_CSTATE_n ; real_T Integrator1_CSTATE_o ; real_T
Integrator2_CSTATE ; real_T Integrator2_CSTATE_f ; real_T
Integrator2_CSTATE_d ; real_T integ_CSTATE ; real_T integrator_CSTATE ;
real_T integrator_CSTATE_l ; } X_control_filtro_dq_mod21_T ; typedef struct {
real_T Integrator1_CSTATE ; real_T Integrator1_CSTATE_n ; real_T
Integrator1_CSTATE_o ; real_T Integrator2_CSTATE ; real_T
Integrator2_CSTATE_f ; real_T Integrator2_CSTATE_d ; real_T integ_CSTATE ;
real_T integrator_CSTATE ; real_T integrator_CSTATE_l ; }
XDot_control_filtro_dq_mod21_T ; typedef struct { boolean_T
Integrator1_CSTATE ; boolean_T Integrator1_CSTATE_n ; boolean_T
Integrator1_CSTATE_o ; boolean_T Integrator2_CSTATE ; boolean_T
Integrator2_CSTATE_f ; boolean_T Integrator2_CSTATE_d ; boolean_T
integ_CSTATE ; boolean_T integrator_CSTATE ; boolean_T integrator_CSTATE_l ;
} XDis_control_filtro_dq_mod21_T ; struct P_control_filtro_dq_mod21_T_ {
real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ;
real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11
; real_T P_12 ; real_T P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ;
real_T P_17 [ 2 ] ; real_T P_18 ; real_T P_19 [ 2 ] ; real_T P_20 ; real_T
P_21 [ 2 ] ; real_T P_22 ; real_T P_23 [ 2 ] ; real_T P_24 ; real_T P_25 ;
real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T P_30 ; real_T
P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ; real_T P_36 ;
real_T P_37 ; real_T P_38 [ 2 ] ; real_T P_39 ; real_T P_40 [ 2 ] ; real_T
P_41 ; real_T P_42 [ 2 ] ; real_T P_43 ; real_T P_44 [ 2 ] ; real_T P_45 ;
real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T
P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 [
2 ] ; real_T P_57 ; real_T P_58 [ 2 ] ; real_T P_59 ; real_T P_60 [ 2 ] ;
real_T P_61 ; real_T P_62 [ 2 ] ; real_T P_63 ; real_T P_64 ; real_T P_65 ;
real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T
P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T P_76 ;
real_T P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ; real_T
P_82 ; real_T P_83 ; real_T P_84 [ 2 ] ; real_T P_85 ; real_T P_86 [ 2 ] ;
real_T P_87 ; real_T P_88 [ 2 ] ; real_T P_89 ; real_T P_90 [ 2 ] ; real_T
P_91 ; real_T P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T P_96 ;
real_T P_97 ; real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101 ;
real_T P_102 ; real_T P_103 ; real_T P_104 ; real_T P_105 [ 2 ] ; real_T
P_106 ; real_T P_107 [ 2 ] ; real_T P_108 ; real_T P_109 [ 2 ] ; real_T P_110
; real_T P_111 [ 2 ] ; real_T P_112 ; real_T P_113 ; real_T P_114 ; real_T
P_115 ; real_T P_116 ; real_T P_117 ; real_T P_118 ; real_T P_119 ; real_T
P_120 ; real_T P_121 ; real_T P_122 ; real_T P_123 [ 2 ] ; real_T P_124 ;
real_T P_125 [ 2 ] ; real_T P_126 ; real_T P_127 [ 2 ] ; real_T P_128 ;
real_T P_129 [ 2 ] ; real_T P_130 ; real_T P_131 ; real_T P_132 ; real_T
P_133 ; real_T P_134 ; real_T P_135 ; real_T P_136 [ 64 ] ; real_T P_137 ;
real_T P_138 ; real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T P_142 ;
real_T P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T P_147 ;
real_T P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T P_152 ;
real_T P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ; real_T P_157 ;
real_T P_158 [ 2 ] ; real_T P_159 [ 3249 ] ; real_T P_160 [ 2 ] ; real_T
P_161 [ 4332 ] ; real_T P_162 [ 2 ] ; real_T P_163 [ 5586 ] ; real_T P_164 [
2 ] ; real_T P_165 [ 7448 ] ; real_T P_166 [ 2 ] ; real_T P_167 [ 57 ] ;
real_T P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ; real_T P_172 [ 3
] ; real_T P_173 [ 3 ] ; real_T P_174 ; real_T P_175 ; real_T P_176 ; real_T
P_177 ; real_T P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ; real_T
P_182 ; real_T P_183 ; real_T P_184 ; real_T P_185 ; real_T P_186 ; real_T
P_187 ; real_T P_188 ; real_T P_189 ; real_T P_190 ; real_T P_191 ; real_T
P_192 ; real_T P_193 ; real_T P_194 ; real_T P_195 ; real_T P_196 ; real_T
P_197 ; real_T P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 ; real_T
P_202 ; real_T P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T
P_207 ; real_T P_208 ; real_T P_209 ; real_T P_210 ; real_T P_211 ; real_T
P_212 ; real_T P_213 ; real_T P_214 ; real_T P_215 ; real_T P_216 ; real_T
P_217 [ 3 ] ; real_T P_218 [ 3 ] ; real_T P_219 ; real_T P_220 ; real_T P_221
; real_T P_222 ; real_T P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 ;
real_T P_227 ; real_T P_228 ; real_T P_229 ; real_T P_230 ; real_T P_231 ;
real_T P_232 ; real_T P_233 ; real_T P_234 [ 3 ] ; real_T P_235 [ 3 ] ;
real_T P_236 ; real_T P_237 ; real_T P_238 ; real_T P_239 ; real_T P_240 ;
real_T P_241 ; real_T P_242 ; real_T P_243 ; real_T P_244 ; real_T P_245 ;
real_T P_246 ; real_T P_247 ; real_T P_248 ; real_T P_249 ; real_T P_250 ;
real_T P_251 ; real_T P_252 ; real_T P_253 ; real_T P_254 ; real_T P_255 ;
real_T P_256 ; real_T P_257 ; real_T P_258 ; real_T P_259 [ 2 ] ; real_T
P_260 ; real_T P_261 [ 2 ] ; real_T P_262 ; real_T P_263 [ 2 ] ; real_T P_264
; real_T P_265 [ 2 ] ; real_T P_266 ; real_T P_267 ; real_T P_268 ; real_T
P_269 ; real_T P_270 ; real_T P_271 ; real_T P_272 ; real_T P_273 ; real_T
P_274 ; real_T P_275 ; real_T P_276 ; real_T P_277 ; real_T P_278 ; real_T
P_279 ; real_T P_280 ; real_T P_281 [ 3 ] ; real_T P_282 [ 3 ] ; real_T P_283
; real_T P_284 [ 3 ] ; real_T P_285 [ 3 ] ; real_T P_286 ; real_T P_287 [ 3 ]
; real_T P_288 [ 3 ] ; real_T P_289 ; real_T P_290 [ 3 ] ; real_T P_291 [ 3 ]
; real_T P_292 ; real_T P_293 [ 3 ] ; real_T P_294 [ 3 ] ; real_T P_295 ;
real_T P_296 [ 3 ] ; real_T P_297 [ 3 ] ; real_T P_298 ; real_T P_299 ;
real_T P_300 ; real_T P_301 ; real_T P_302 ; real_T P_303 ; real_T P_304 ;
real_T P_305 ; real_T P_306 ; real_T P_307 ; real_T P_308 ; real_T P_309 ;
real_T P_310 ; real_T P_311 ; real_T P_312 ; real_T P_313 ; real_T P_314 ;
real_T P_315 ; real_T P_316 ; real_T P_317 ; real_T P_318 ; real_T P_319 ;
real_T P_320 ; real_T P_321 ; real_T P_322 ; real_T P_323 ; real_T P_324 ;
real_T P_325 ; real_T P_326 ; real_T P_327 ; real_T P_328 ; } ; extern
P_control_filtro_dq_mod21_T control_filtro_dq_mod21_rtDefaultP ;
#endif
