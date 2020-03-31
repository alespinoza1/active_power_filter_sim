#include "__cf_control_filtro_dq_mod21.h"
#include <math.h>
#include "control_filtro_dq_mod21_acc.h"
#include "control_filtro_dq_mod21_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T control_filtro_dq_mod21_acc_rt_TDelayInterpolate (
real_T tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T
bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput
, boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } real_T look1_binlxpw ( real_T
u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) {
real_T frac ; uint32_T iRght ; uint32_T iLeft ; uint32_T bpIdx ; if ( u0 <=
bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [
0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx = maxIndex >> 1U ; iLeft
= 0U ; iRght = maxIndex ; while ( iRght - iLeft > 1U ) { if ( u0 < bp0 [
bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; } bpIdx = ( iRght +
iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [ iLeft + 1U ] - bp0
[ iLeft ] ) ; } else { iLeft = maxIndex - 1U ; frac = ( u0 - bp0 [ maxIndex -
1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; } return ( table [
iLeft + 1U ] - table [ iLeft ] ) * frac + table [ iLeft ] ; } void
rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * *
path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { _ssSet_slErrMsg ( S ,
diag ) ; } void rt_ssReportDiagnosticAsWarning ( SimStruct * S , void * diag
) { _ssReportDiagnosticAsWarning ( S , diag ) ; } static void mdlOutputs (
SimStruct * S , int_T tid ) { real_T B_11_116_0 ; real_T B_11_142_0 ; real_T
B_11_258_0 ; real_T B_11_284_0 ; real_T B_11_401_0 ; real_T B_11_427_0 ;
real_T B_11_761_0 ; real_T B_11_767_0 ; real_T B_11_772_0 ; real_T
rtb_B_11_60_0 ; real_T rtb_B_11_61_0 ; real_T rtb_B_11_75_0 ; real_T
rtb_B_11_527_0 [ 6 ] ; real_T rtb_B_11_538_0 [ 6 ] ; real_T rtb_B_11_68_0 ;
real_T rtb_B_11_72_0 ; real_T rtb_B_11_76_0 ; int32_T i ;
B_control_filtro_dq_mod21_T * _rtB ; P_control_filtro_dq_mod21_T * _rtP ;
X_control_filtro_dq_mod21_T * _rtX ; DW_control_filtro_dq_mod21_T * _rtDW ;
_rtDW = ( ( DW_control_filtro_dq_mod21_T * ) ssGetRootDWork ( S ) ) ; _rtX =
( ( X_control_filtro_dq_mod21_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_control_filtro_dq_mod21_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB ->
B_11_10_0 = muDoubleScalarSin ( _rtP -> P_148 * ssGetTaskTime ( S , 0 ) +
_rtP -> P_149 ) * _rtP -> P_146 + _rtP -> P_147 ; _rtB -> B_11_11_0 =
muDoubleScalarSin ( _rtP -> P_152 * ssGetTaskTime ( S , 0 ) + _rtP -> P_153 )
* _rtP -> P_150 + _rtP -> P_151 ; _rtB -> B_11_12_0 = muDoubleScalarSin (
_rtP -> P_156 * ssGetTaskTime ( S , 0 ) + _rtP -> P_157 ) * _rtP -> P_154 +
_rtP -> P_155 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
ssCallAccelRunBlock ( S , 11 , 13 , SS_CALL_MDL_OUTPUTS ) ; } rtb_B_11_60_0 =
ssGetTaskTime ( S , 0 ) ; if ( rtb_B_11_60_0 < _rtP -> P_168 ) { _rtB ->
B_11_34_0 = _rtP -> P_169 ; } else { _rtB -> B_11_34_0 = _rtP -> P_170 ; }
_rtB -> B_11_43_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_11_39_0 , _rtB -> B_11_41_0 ) , _rtP -> P_173 , _rtP -> P_172 , 2U ) ;
_rtB -> B_11_44_0 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { _rtB -> B_11_48_0 [ 0 ] = _rtP -> P_174 * _rtB -> B_11_13_0 [ 91 ] *
_rtP -> P_177 ; _rtB -> B_11_48_0 [ 1 ] = _rtP -> P_175 * _rtB -> B_11_13_0 [
94 ] * _rtP -> P_177 ; _rtB -> B_11_48_0 [ 2 ] = _rtP -> P_176 * _rtB ->
B_11_13_0 [ 95 ] * _rtP -> P_177 ; _rtB -> B_11_50_0 = ( _rtDW ->
Integrator_DSTATE >= _rtB -> B_11_49_0 ) ; if ( _rtDW ->
Initial_FirstOutputTime ) { _rtDW -> Initial_FirstOutputTime = false ; _rtB
-> B_11_52_0 = _rtP -> P_180 ; } else { _rtB -> B_11_52_0 = _rtDW ->
Integrator_DSTATE + _rtP -> P_179 ; } if ( _rtB -> B_11_50_0 && ( _rtDW ->
Integrator_PrevResetState <= 0 ) ) { _rtDW -> Integrator_DSTATE = _rtB ->
B_11_52_0 ; } _rtB -> B_11_53_0 = _rtDW -> Integrator_DSTATE ; _rtB ->
B_11_57_0 [ 0 ] = ( ( muDoubleScalarSin ( ( _rtB -> B_11_53_0 +
1.5707963267948966 ) - 2.0943951023931953 ) * _rtB -> B_11_48_0 [ 1 ] +
muDoubleScalarSin ( _rtB -> B_11_53_0 + 1.5707963267948966 ) * _rtB ->
B_11_48_0 [ 0 ] ) + muDoubleScalarSin ( ( _rtB -> B_11_53_0 +
1.5707963267948966 ) + 2.0943951023931953 ) * _rtB -> B_11_48_0 [ 2 ] ) *
_rtP -> P_182 ; _rtB -> B_11_57_0 [ 1 ] = ( ( muDoubleScalarCos ( ( _rtB ->
B_11_53_0 + 1.5707963267948966 ) - 2.0943951023931953 ) * _rtB -> B_11_48_0 [
1 ] + muDoubleScalarCos ( _rtB -> B_11_53_0 + 1.5707963267948966 ) * _rtB ->
B_11_48_0 [ 0 ] ) + muDoubleScalarCos ( ( _rtB -> B_11_53_0 +
1.5707963267948966 ) + 2.0943951023931953 ) * _rtB -> B_11_48_0 [ 2 ] ) *
_rtP -> P_182 ; _rtB -> B_11_57_0 [ 2 ] = ( ( _rtB -> B_11_48_0 [ 0 ] + _rtB
-> B_11_48_0 [ 1 ] ) + _rtB -> B_11_48_0 [ 2 ] ) * 0.70710678118654746 * _rtP
-> P_182 ; } rtb_B_11_60_0 = _rtB -> B_11_58_0 * _rtX -> Integrator1_CSTATE ;
i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_11_63_0 = _rtP ->
P_186 * _rtB -> B_11_13_0 [ 83 ] ; _rtB -> B_11_64_0 = _rtB -> B_11_62_0 -
_rtB -> B_11_63_0 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB
-> B_11_67_0 = _rtP -> P_187 * _rtB -> B_11_64_0 + _rtDW ->
Integrator_DSTATE_l ; } rtb_B_11_68_0 = ( _rtB -> B_11_57_0 [ 0 ] -
rtb_B_11_60_0 ) - _rtB -> B_11_67_0 ; rtb_B_11_61_0 = _rtB -> B_11_69_0 *
_rtX -> Integrator1_CSTATE_n ; rtb_B_11_72_0 = _rtB -> B_11_57_0 [ 1 ] -
rtb_B_11_61_0 ; rtb_B_11_75_0 = _rtB -> B_11_73_0 * _rtX ->
Integrator1_CSTATE_o ; rtb_B_11_76_0 = _rtB -> B_11_57_0 [ 2 ] -
rtb_B_11_75_0 ; _rtB -> B_11_80_0 [ 0 ] = ( ( muDoubleScalarSin ( _rtB ->
B_11_53_0 + 1.5707963267948966 ) * rtb_B_11_68_0 + muDoubleScalarCos ( _rtB
-> B_11_53_0 + 1.5707963267948966 ) * rtb_B_11_72_0 ) + 0.70710678118654746 *
rtb_B_11_76_0 ) * _rtP -> P_194 ; _rtB -> B_11_80_0 [ 1 ] = ( (
muDoubleScalarSin ( ( _rtB -> B_11_53_0 + 1.5707963267948966 ) -
2.0943951023931953 ) * rtb_B_11_68_0 + muDoubleScalarCos ( ( _rtB ->
B_11_53_0 + 1.5707963267948966 ) - 2.0943951023931953 ) * rtb_B_11_72_0 ) +
0.70710678118654746 * rtb_B_11_76_0 ) * _rtP -> P_194 ; _rtB -> B_11_80_0 [ 2
] = ( ( muDoubleScalarSin ( ( _rtB -> B_11_53_0 + 1.5707963267948966 ) +
2.0943951023931953 ) * rtb_B_11_68_0 + muDoubleScalarCos ( ( _rtB ->
B_11_53_0 + 1.5707963267948966 ) + 2.0943951023931953 ) * rtb_B_11_72_0 ) +
0.70710678118654746 * rtb_B_11_76_0 ) * _rtP -> P_194 ; i = ssIsSampleHit ( S
, 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_11_84_0 [ 0 ] = _rtP -> P_195 * _rtB ->
B_11_13_0 [ 86 ] * _rtP -> P_198 ; _rtB -> B_11_84_0 [ 1 ] = _rtP -> P_196 *
_rtB -> B_11_13_0 [ 87 ] * _rtP -> P_198 ; _rtB -> B_11_84_0 [ 2 ] = _rtP ->
P_197 * _rtB -> B_11_13_0 [ 88 ] * _rtP -> P_198 ; _rtB -> B_11_88_0 [ 0 ] =
_rtP -> P_199 * _rtB -> B_11_13_0 [ 67 ] * _rtP -> P_202 ; _rtB -> B_11_88_0
[ 1 ] = _rtP -> P_200 * _rtB -> B_11_13_0 [ 69 ] * _rtP -> P_202 ; _rtB ->
B_11_88_0 [ 2 ] = _rtP -> P_201 * _rtB -> B_11_13_0 [ 70 ] * _rtP -> P_202 ;
} ssCallAccelRunBlock ( S , 11 , 89 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_11_90_0 = _rtP -> P_203 * _rtB -> B_11_89_0 [ 0 ] ; _rtB -> B_11_92_0 = (
_rtB -> B_11_43_0 <= _rtB -> B_11_90_0 ) ; _rtB -> B_11_94_0 = ! ( _rtB ->
B_11_92_0 != 0.0 ) ; _rtB -> B_11_103_0 = ( _rtB -> B_11_43_0 <= _rtP ->
P_204 * _rtB -> B_11_90_0 ) ; _rtB -> B_11_105_0 = ! ( _rtB -> B_11_103_0 !=
0.0 ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK
. TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_205 ; B_11_116_0 =
control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_206 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_11_118_0 = ( B_11_116_0 <= _rtB -> B_11_90_0 ) ; _rtB ->
B_11_120_0 = ! ( _rtB -> B_11_118_0 != 0.0 ) ; _rtB -> B_11_129_0 = (
B_11_116_0 <= _rtP -> P_207 * _rtB -> B_11_90_0 ) ; _rtB -> B_11_131_0 = ! (
_rtB -> B_11_129_0 != 0.0 ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_n . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_208 ;
B_11_142_0 = control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_o .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_o . Last , _rtDW ->
TransportDelay_IWORK_o . Tail , _rtDW -> TransportDelay_IWORK_o . Head , _rtP
-> P_209 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_11_144_0 = (
B_11_142_0 <= _rtB -> B_11_90_0 ) ; _rtB -> B_11_146_0 = ! ( _rtB ->
B_11_144_0 != 0.0 ) ; _rtB -> B_11_155_0 = ( B_11_142_0 <= _rtP -> P_210 *
_rtB -> B_11_90_0 ) ; _rtB -> B_11_157_0 = ! ( _rtB -> B_11_155_0 != 0.0 ) ;
i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_11_192_0 = _rtP
-> P_213 * _rtB -> B_11_13_0 [ 79 ] ; _rtB -> B_11_211_0 = _rtP -> P_215 *
_rtB -> B_11_13_0 [ 73 ] ; } rtb_B_11_68_0 = look1_binlxpw (
muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_11_227_0 , _rtB -> B_11_229_0 )
, _rtP -> P_218 , _rtP -> P_217 , 2U ) ; rtb_B_11_72_0 = _rtP -> P_219 * _rtB
-> B_11_89_0 [ 1 ] ; _rtB -> B_11_234_0 = ( rtb_B_11_68_0 <= rtb_B_11_72_0 )
; _rtB -> B_11_236_0 = ! ( _rtB -> B_11_234_0 != 0.0 ) ; _rtB -> B_11_245_0 =
( rtb_B_11_68_0 <= _rtP -> P_220 * rtb_B_11_72_0 ) ; _rtB -> B_11_247_0 = ! (
_rtB -> B_11_245_0 != 0.0 ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_f . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_221 ;
B_11_258_0 = control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_e .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_e . Last , _rtDW ->
TransportDelay_IWORK_e . Tail , _rtDW -> TransportDelay_IWORK_e . Head , _rtP
-> P_222 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_11_260_0 = (
B_11_258_0 <= rtb_B_11_72_0 ) ; _rtB -> B_11_262_0 = ! ( _rtB -> B_11_260_0
!= 0.0 ) ; _rtB -> B_11_271_0 = ( B_11_258_0 <= _rtP -> P_223 * rtb_B_11_72_0
) ; _rtB -> B_11_273_0 = ! ( _rtB -> B_11_271_0 != 0.0 ) ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_224 ; B_11_284_0 =
control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_p . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_p . Last , _rtDW -> TransportDelay_IWORK_p .
Tail , _rtDW -> TransportDelay_IWORK_p . Head , _rtP -> P_225 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_11_286_0 = ( B_11_284_0 <= rtb_B_11_72_0 ) ;
_rtB -> B_11_288_0 = ! ( _rtB -> B_11_286_0 != 0.0 ) ; _rtB -> B_11_297_0 = (
B_11_284_0 <= _rtP -> P_226 * rtb_B_11_72_0 ) ; _rtB -> B_11_299_0 = ! ( _rtB
-> B_11_297_0 != 0.0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
_rtB -> B_11_316_0 = _rtP -> P_228 * _rtB -> B_11_13_0 [ 84 ] ; _rtB ->
B_11_335_0 = _rtP -> P_230 * _rtB -> B_11_13_0 [ 80 ] ; _rtB -> B_11_354_0 =
_rtP -> P_232 * _rtB -> B_11_13_0 [ 74 ] ; } rtb_B_11_68_0 = look1_binlxpw (
muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_11_370_0 , _rtB -> B_11_372_0 )
, _rtP -> P_235 , _rtP -> P_234 , 2U ) ; rtb_B_11_72_0 = _rtP -> P_236 * _rtB
-> B_11_89_0 [ 2 ] ; _rtB -> B_11_377_0 = ( rtb_B_11_68_0 <= rtb_B_11_72_0 )
; _rtB -> B_11_379_0 = ! ( _rtB -> B_11_377_0 != 0.0 ) ; _rtB -> B_11_388_0 =
( rtb_B_11_68_0 <= _rtP -> P_237 * rtb_B_11_72_0 ) ; _rtB -> B_11_390_0 = ! (
_rtB -> B_11_388_0 != 0.0 ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_238 ;
B_11_401_0 = control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_b .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_b . Last , _rtDW ->
TransportDelay_IWORK_b . Tail , _rtDW -> TransportDelay_IWORK_b . Head , _rtP
-> P_239 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_11_403_0 = (
B_11_401_0 <= rtb_B_11_72_0 ) ; _rtB -> B_11_405_0 = ! ( _rtB -> B_11_403_0
!= 0.0 ) ; _rtB -> B_11_414_0 = ( B_11_401_0 <= _rtP -> P_240 * rtb_B_11_72_0
) ; _rtB -> B_11_416_0 = ! ( _rtB -> B_11_414_0 != 0.0 ) ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_241 ; B_11_427_0 =
control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_os . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_os . Last , _rtDW -> TransportDelay_IWORK_os .
Tail , _rtDW -> TransportDelay_IWORK_os . Head , _rtP -> P_242 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_11_429_0 = ( B_11_427_0 <= rtb_B_11_72_0 ) ;
_rtB -> B_11_431_0 = ! ( _rtB -> B_11_429_0 != 0.0 ) ; _rtB -> B_11_440_0 = (
B_11_427_0 <= _rtP -> P_243 * rtb_B_11_72_0 ) ; _rtB -> B_11_442_0 = ! ( _rtB
-> B_11_440_0 != 0.0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
_rtB -> B_11_459_0 = _rtP -> P_245 * _rtB -> B_11_13_0 [ 85 ] ; _rtB ->
B_11_478_0 = _rtP -> P_247 * _rtB -> B_11_13_0 [ 81 ] ; _rtB -> B_11_497_0 =
_rtP -> P_249 * _rtB -> B_11_13_0 [ 75 ] ; _rtB -> B_11_517_0 [ 0 ] = _rtP ->
P_250 * _rtB -> B_11_13_0 [ 90 ] * _rtP -> P_253 ; _rtB -> B_11_517_0 [ 1 ] =
_rtP -> P_251 * _rtB -> B_11_13_0 [ 92 ] * _rtP -> P_253 ; _rtB -> B_11_517_0
[ 2 ] = _rtP -> P_252 * _rtB -> B_11_13_0 [ 93 ] * _rtP -> P_253 ; _rtB ->
B_11_518_0 = _rtP -> P_254 * _rtB -> B_11_13_0 [ 89 ] ; ssCallAccelRunBlock (
S , 11 , 519 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 11 , 520 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtB ->
B_11_522_0 ) { if ( ! _rtDW -> TrueRMS_MODE_c ) { if ( ssGetTaskTime ( S , 1
) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} _rtDW -> Integ4_SYSTEM_ENABLE_a = 1U ; _rtDW -> TrueRMS_MODE_c = true ; } }
else { if ( _rtDW -> TrueRMS_MODE_c ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; for ( i = 0 ; i < 6 ; i ++
) { _rtDW -> Integ4_DSTATE_m [ i ] = _rtB -> B_5_2_0 [ i ] ; } _rtDW ->
TrueRMS_MODE_c = false ; } } } if ( _rtDW -> TrueRMS_MODE_c ) { _rtB ->
B_5_1_0 [ 0 ] = _rtB -> B_11_517_0 [ 0 ] * _rtB -> B_11_517_0 [ 0 ] ; _rtB ->
B_5_1_0 [ 3 ] = _rtB -> B_11_48_0 [ 0 ] * _rtB -> B_11_48_0 [ 0 ] ; _rtB ->
B_5_1_0 [ 1 ] = _rtB -> B_11_517_0 [ 1 ] * _rtB -> B_11_517_0 [ 1 ] ; _rtB ->
B_5_1_0 [ 4 ] = _rtB -> B_11_48_0 [ 1 ] * _rtB -> B_11_48_0 [ 1 ] ; _rtB ->
B_5_1_0 [ 2 ] = _rtB -> B_11_517_0 [ 2 ] * _rtB -> B_11_517_0 [ 2 ] ; _rtB ->
B_5_1_0 [ 5 ] = _rtB -> B_11_48_0 [ 2 ] * _rtB -> B_11_48_0 [ 2 ] ; for ( i =
0 ; i < 6 ; i ++ ) { if ( _rtDW -> Integ4_SYSTEM_ENABLE_a != 0 ) { _rtB ->
B_5_2_0 [ i ] = _rtDW -> Integ4_DSTATE_m [ i ] ; } else { _rtB -> B_5_2_0 [ i
] = _rtP -> P_53 * _rtB -> B_5_1_0 [ i ] + _rtDW -> Integ4_DSTATE_m [ i ] ; }
} _rtB -> B_5_3_0 = _rtP -> P_55 ; ssCallAccelRunBlock ( S , 5 , 4 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 1 ) >= _rtB -> B_5_3_0 ) {
for ( i = 0 ; i < 6 ; i ++ ) { _rtB -> B_5_10_0 [ i ] = ( _rtB -> B_5_2_0 [ i
] - _rtB -> B_5_4_0 [ i ] ) * _rtP -> P_65 + ( _rtP -> P_50 * _rtB -> B_5_1_0
[ i ] - _rtP -> P_51 * _rtDW -> UnitDelay_DSTATE_p [ i ] ) ; } } else { for (
i = 0 ; i < 6 ; i ++ ) { _rtB -> B_5_10_0 [ i ] = _rtDW ->
UnitDelay1_DSTATE_l [ i ] ; } } for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtB ->
B_5_10_0 [ i ] > _rtP -> P_67 ) { rtb_B_11_68_0 = _rtP -> P_67 ; } else if (
_rtB -> B_5_10_0 [ i ] < _rtP -> P_68 ) { rtb_B_11_68_0 = _rtP -> P_68 ; }
else { rtb_B_11_68_0 = _rtB -> B_5_10_0 [ i ] ; } _rtB -> B_5_12_0 [ i ] =
muDoubleScalarSqrt ( rtb_B_11_68_0 ) ; } if ( ssIsMajorTimeStep ( S ) != 0 )
{ srUpdateBC ( _rtDW -> TrueRMS_SubsysRanBC_i ) ; } } if ( ssIsMajorTimeStep
( S ) != 0 ) { if ( _rtB -> B_11_524_0 ) { if ( ! _rtDW -> RMS_MODE_i ) { if
( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> systemEnable_g
= 1 ; _rtDW -> Integ4_SYSTEM_ENABLE_k = 1U ; _rtDW -> systemEnable_h = 1 ;
_rtDW -> Integ4_SYSTEM_ENABLE_g = 1U ; _rtDW -> RMS_MODE_i = true ; } } else
{ if ( _rtDW -> RMS_MODE_i ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; for ( i = 0 ; i < 6 ; i ++ ) { _rtDW -> Integ4_DSTATE_h0 [ i ] = _rtB ->
B_3_2_0 [ i ] ; _rtDW -> Integ4_DSTATE_l [ i ] = _rtB -> B_3_14_0 [ i ] ; }
_rtDW -> RMS_MODE_i = false ; } } } if ( _rtDW -> RMS_MODE_i ) { if ( _rtDW
-> systemEnable_g != 0 ) { _rtDW -> lastSin_o = muDoubleScalarSin ( _rtP ->
P_9 * ssGetTaskTime ( S , 1 ) ) ; _rtDW -> lastCos_b = muDoubleScalarCos (
_rtP -> P_9 * ssGetTaskTime ( S , 1 ) ) ; _rtDW -> systemEnable_g = 0 ; }
rtb_B_11_68_0 = ( ( _rtDW -> lastSin_o * _rtP -> P_13 + _rtDW -> lastCos_b *
_rtP -> P_12 ) * _rtP -> P_11 + ( _rtDW -> lastCos_b * _rtP -> P_13 - _rtDW
-> lastSin_o * _rtP -> P_12 ) * _rtP -> P_10 ) * _rtP -> P_7 + _rtP -> P_8 ;
_rtB -> B_3_1_0 [ 0 ] = _rtB -> B_11_517_0 [ 0 ] * rtb_B_11_68_0 ; _rtB ->
B_3_1_0 [ 3 ] = _rtB -> B_11_48_0 [ 0 ] * rtb_B_11_68_0 ; _rtB -> B_3_1_0 [ 1
] = _rtB -> B_11_517_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_3_1_0 [ 4 ] = _rtB
-> B_11_48_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_3_1_0 [ 2 ] = _rtB ->
B_11_517_0 [ 2 ] * rtb_B_11_68_0 ; _rtB -> B_3_1_0 [ 5 ] = _rtB -> B_11_48_0
[ 2 ] * rtb_B_11_68_0 ; for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtDW ->
Integ4_SYSTEM_ENABLE_k != 0 ) { _rtB -> B_3_2_0 [ i ] = _rtDW ->
Integ4_DSTATE_h0 [ i ] ; } else { _rtB -> B_3_2_0 [ i ] = _rtP -> P_14 * _rtB
-> B_3_1_0 [ i ] + _rtDW -> Integ4_DSTATE_h0 [ i ] ; } } _rtB -> B_3_3_0 =
_rtP -> P_16 ; ssCallAccelRunBlock ( S , 3 , 4 , SS_CALL_MDL_OUTPUTS ) ; if (
ssGetTaskTime ( S , 1 ) >= _rtB -> B_3_3_0 ) { for ( i = 0 ; i < 6 ; i ++ ) {
_rtB -> B_3_11_0 [ i ] = ( _rtB -> B_3_2_0 [ i ] - _rtB -> B_3_4_0 [ i ] ) *
_rtP -> P_25 + ( _rtP -> P_5 * _rtB -> B_3_1_0 [ i ] - _rtP -> P_4 * _rtDW ->
UnitDelay_DSTATE_pe [ i ] ) ; } } else { for ( i = 0 ; i < 6 ; i ++ ) { _rtB
-> B_3_11_0 [ i ] = _rtDW -> UnitDelay1_DSTATE_n [ i ] ; } } if ( _rtDW ->
systemEnable_h != 0 ) { _rtDW -> lastSin_k = muDoubleScalarSin ( _rtP -> P_30
* ssGetTaskTime ( S , 1 ) ) ; _rtDW -> lastCos_f = muDoubleScalarCos ( _rtP
-> P_30 * ssGetTaskTime ( S , 1 ) ) ; _rtDW -> systemEnable_h = 0 ; }
rtb_B_11_68_0 = ( ( _rtDW -> lastSin_k * _rtP -> P_34 + _rtDW -> lastCos_f *
_rtP -> P_33 ) * _rtP -> P_32 + ( _rtDW -> lastCos_f * _rtP -> P_34 - _rtDW
-> lastSin_k * _rtP -> P_33 ) * _rtP -> P_31 ) * _rtP -> P_28 + _rtP -> P_29
; _rtB -> B_3_13_0 [ 0 ] = _rtB -> B_11_517_0 [ 0 ] * rtb_B_11_68_0 ; _rtB ->
B_3_13_0 [ 3 ] = _rtB -> B_11_48_0 [ 0 ] * rtb_B_11_68_0 ; _rtB -> B_3_13_0 [
1 ] = _rtB -> B_11_517_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_3_13_0 [ 4 ] =
_rtB -> B_11_48_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_3_13_0 [ 2 ] = _rtB ->
B_11_517_0 [ 2 ] * rtb_B_11_68_0 ; _rtB -> B_3_13_0 [ 5 ] = _rtB -> B_11_48_0
[ 2 ] * rtb_B_11_68_0 ; for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtDW ->
Integ4_SYSTEM_ENABLE_g != 0 ) { _rtB -> B_3_14_0 [ i ] = _rtDW ->
Integ4_DSTATE_l [ i ] ; } else { _rtB -> B_3_14_0 [ i ] = _rtP -> P_35 * _rtB
-> B_3_13_0 [ i ] + _rtDW -> Integ4_DSTATE_l [ i ] ; } } _rtB -> B_3_15_0 =
_rtP -> P_37 ; ssCallAccelRunBlock ( S , 3 , 16 , SS_CALL_MDL_OUTPUTS ) ; if
( ssGetTaskTime ( S , 1 ) >= _rtB -> B_3_15_0 ) { for ( i = 0 ; i < 6 ; i ++
) { _rtB -> B_3_23_0 [ i ] = ( _rtB -> B_3_14_0 [ i ] - _rtB -> B_3_16_0 [ i
] ) * _rtP -> P_46 + ( _rtP -> P_3 * _rtB -> B_3_13_0 [ i ] - _rtP -> P_2 *
_rtDW -> UnitDelay_DSTATE_o [ i ] ) ; } } else { for ( i = 0 ; i < 6 ; i ++ )
{ _rtB -> B_3_23_0 [ i ] = _rtDW -> UnitDelay1_DSTATE_ib [ i ] ; } } for ( i
= 0 ; i < 6 ; i ++ ) { _rtB -> B_3_26_0 [ i ] = _rtP -> P_49 *
muDoubleScalarHypot ( _rtB -> B_3_11_0 [ i ] , _rtB -> B_3_23_0 [ i ] ) ; }
if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW -> RMS_SubsysRanBC_f
) ; } } for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtB -> B_11_522_0 ) {
rtb_B_11_68_0 = _rtB -> B_5_12_0 [ i ] ; } else { rtb_B_11_68_0 = _rtB ->
B_3_26_0 [ i ] ; } rtb_B_11_527_0 [ i ] = rtb_B_11_68_0 * rtb_B_11_68_0 ; }
if ( _rtDW -> Integ4_SYSTEM_ENABLE != 0 ) { _rtB -> B_11_528_0 [ 0 ] = _rtDW
-> Integ4_DSTATE [ 0 ] ; _rtB -> B_11_528_0 [ 3 ] = _rtDW -> Integ4_DSTATE [
3 ] ; _rtB -> B_11_528_0 [ 1 ] = _rtDW -> Integ4_DSTATE [ 1 ] ; _rtB ->
B_11_528_0 [ 4 ] = _rtDW -> Integ4_DSTATE [ 4 ] ; _rtB -> B_11_528_0 [ 2 ] =
_rtDW -> Integ4_DSTATE [ 2 ] ; _rtB -> B_11_528_0 [ 5 ] = _rtDW ->
Integ4_DSTATE [ 5 ] ; } else { _rtB -> B_11_528_0 [ 0 ] = _rtP -> P_256 *
_rtB -> B_11_517_0 [ 0 ] + _rtDW -> Integ4_DSTATE [ 0 ] ; _rtB -> B_11_528_0
[ 3 ] = _rtP -> P_256 * _rtB -> B_11_48_0 [ 0 ] + _rtDW -> Integ4_DSTATE [ 3
] ; _rtB -> B_11_528_0 [ 1 ] = _rtP -> P_256 * _rtB -> B_11_517_0 [ 1 ] +
_rtDW -> Integ4_DSTATE [ 1 ] ; _rtB -> B_11_528_0 [ 4 ] = _rtP -> P_256 *
_rtB -> B_11_48_0 [ 1 ] + _rtDW -> Integ4_DSTATE [ 4 ] ; _rtB -> B_11_528_0 [
2 ] = _rtP -> P_256 * _rtB -> B_11_517_0 [ 2 ] + _rtDW -> Integ4_DSTATE [ 2 ]
; _rtB -> B_11_528_0 [ 5 ] = _rtP -> P_256 * _rtB -> B_11_48_0 [ 2 ] + _rtDW
-> Integ4_DSTATE [ 5 ] ; } _rtB -> B_11_529_0 = _rtP -> P_258 ;
ssCallAccelRunBlock ( S , 11 , 530 , SS_CALL_MDL_OUTPUTS ) ; if (
ssGetTaskTime ( S , 1 ) >= _rtB -> B_11_529_0 ) { _rtB -> B_11_537_0 [ 0 ] =
( _rtB -> B_11_528_0 [ 0 ] - _rtB -> B_11_530_0 [ 0 ] ) * _rtP -> P_267 + (
_rtP -> P_1 * _rtB -> B_11_517_0 [ 0 ] - _rtP -> P_0 * _rtDW ->
UnitDelay_DSTATE [ 0 ] ) ; _rtB -> B_11_537_0 [ 3 ] = ( _rtB -> B_11_528_0 [
3 ] - _rtB -> B_11_530_0 [ 3 ] ) * _rtP -> P_267 + ( _rtP -> P_1 * _rtB ->
B_11_48_0 [ 0 ] - _rtP -> P_0 * _rtDW -> UnitDelay_DSTATE [ 3 ] ) ; _rtB ->
B_11_537_0 [ 1 ] = ( _rtB -> B_11_528_0 [ 1 ] - _rtB -> B_11_530_0 [ 1 ] ) *
_rtP -> P_267 + ( _rtP -> P_1 * _rtB -> B_11_517_0 [ 1 ] - _rtP -> P_0 *
_rtDW -> UnitDelay_DSTATE [ 1 ] ) ; _rtB -> B_11_537_0 [ 4 ] = ( _rtB ->
B_11_528_0 [ 4 ] - _rtB -> B_11_530_0 [ 4 ] ) * _rtP -> P_267 + ( _rtP -> P_1
* _rtB -> B_11_48_0 [ 1 ] - _rtP -> P_0 * _rtDW -> UnitDelay_DSTATE [ 4 ] ) ;
_rtB -> B_11_537_0 [ 2 ] = ( _rtB -> B_11_528_0 [ 2 ] - _rtB -> B_11_530_0 [
2 ] ) * _rtP -> P_267 + ( _rtP -> P_1 * _rtB -> B_11_517_0 [ 2 ] - _rtP ->
P_0 * _rtDW -> UnitDelay_DSTATE [ 2 ] ) ; _rtB -> B_11_537_0 [ 5 ] = ( _rtB
-> B_11_528_0 [ 5 ] - _rtB -> B_11_530_0 [ 5 ] ) * _rtP -> P_267 + ( _rtP ->
P_1 * _rtB -> B_11_48_0 [ 2 ] - _rtP -> P_0 * _rtDW -> UnitDelay_DSTATE [ 5 ]
) ; } else { for ( i = 0 ; i < 6 ; i ++ ) { _rtB -> B_11_537_0 [ i ] = _rtDW
-> UnitDelay1_DSTATE [ i ] ; } } for ( i = 0 ; i < 6 ; i ++ ) {
rtb_B_11_538_0 [ i ] = _rtB -> B_11_537_0 [ i ] * _rtB -> B_11_537_0 [ i ] ;
} if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtB -> B_11_540_0 ) { if ( !
_rtDW -> TrueRMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) )
{ ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integ4_SYSTEM_ENABLE_n = 1U ; _rtDW -> TrueRMS_MODE = true ; } } else { if (
_rtDW -> TrueRMS_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
for ( i = 0 ; i < 6 ; i ++ ) { _rtDW -> Integ4_DSTATE_h [ i ] = _rtB ->
B_10_2_0 [ i ] ; } _rtDW -> TrueRMS_MODE = false ; } } } if ( _rtDW ->
TrueRMS_MODE ) { _rtB -> B_10_1_0 [ 0 ] = _rtB -> B_11_517_0 [ 0 ] * _rtB ->
B_11_517_0 [ 0 ] ; _rtB -> B_10_1_0 [ 3 ] = _rtB -> B_11_48_0 [ 0 ] * _rtB ->
B_11_48_0 [ 0 ] ; _rtB -> B_10_1_0 [ 1 ] = _rtB -> B_11_517_0 [ 1 ] * _rtB ->
B_11_517_0 [ 1 ] ; _rtB -> B_10_1_0 [ 4 ] = _rtB -> B_11_48_0 [ 1 ] * _rtB ->
B_11_48_0 [ 1 ] ; _rtB -> B_10_1_0 [ 2 ] = _rtB -> B_11_517_0 [ 2 ] * _rtB ->
B_11_517_0 [ 2 ] ; _rtB -> B_10_1_0 [ 5 ] = _rtB -> B_11_48_0 [ 2 ] * _rtB ->
B_11_48_0 [ 2 ] ; for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtDW ->
Integ4_SYSTEM_ENABLE_n != 0 ) { _rtB -> B_10_2_0 [ i ] = _rtDW ->
Integ4_DSTATE_h [ i ] ; } else { _rtB -> B_10_2_0 [ i ] = _rtP -> P_120 *
_rtB -> B_10_1_0 [ i ] + _rtDW -> Integ4_DSTATE_h [ i ] ; } } _rtB ->
B_10_3_0 = _rtP -> P_122 ; ssCallAccelRunBlock ( S , 10 , 4 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 1 ) >= _rtB -> B_10_3_0 ) {
for ( i = 0 ; i < 6 ; i ++ ) { _rtB -> B_10_10_0 [ i ] = ( _rtB -> B_10_2_0 [
i ] - _rtB -> B_10_4_0 [ i ] ) * _rtP -> P_132 + ( _rtP -> P_117 * _rtB ->
B_10_1_0 [ i ] - _rtP -> P_118 * _rtDW -> UnitDelay_DSTATE_a [ i ] ) ; } }
else { for ( i = 0 ; i < 6 ; i ++ ) { _rtB -> B_10_10_0 [ i ] = _rtDW ->
UnitDelay1_DSTATE_g [ i ] ; } } for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtB ->
B_10_10_0 [ i ] > _rtP -> P_134 ) { rtb_B_11_68_0 = _rtP -> P_134 ; } else if
( _rtB -> B_10_10_0 [ i ] < _rtP -> P_135 ) { rtb_B_11_68_0 = _rtP -> P_135 ;
} else { rtb_B_11_68_0 = _rtB -> B_10_10_0 [ i ] ; } _rtB -> B_10_12_0 [ i ]
= muDoubleScalarSqrt ( rtb_B_11_68_0 ) ; } if ( ssIsMajorTimeStep ( S ) != 0
) { srUpdateBC ( _rtDW -> TrueRMS_SubsysRanBC ) ; } } if ( ssIsMajorTimeStep
( S ) != 0 ) { if ( _rtB -> B_11_542_0 ) { if ( ! _rtDW -> RMS_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> systemEnable =
1 ; _rtDW -> Integ4_SYSTEM_ENABLE_l = 1U ; _rtDW -> systemEnable_p = 1 ;
_rtDW -> Integ4_SYSTEM_ENABLE_b = 1U ; _rtDW -> RMS_MODE = true ; } } else {
if ( _rtDW -> RMS_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
for ( i = 0 ; i < 6 ; i ++ ) { _rtDW -> Integ4_DSTATE_b [ i ] = _rtB ->
B_8_2_0 [ i ] ; _rtDW -> Integ4_DSTATE_o [ i ] = _rtB -> B_8_14_0 [ i ] ; }
_rtDW -> RMS_MODE = false ; } } } if ( _rtDW -> RMS_MODE ) { if ( _rtDW ->
systemEnable != 0 ) { _rtDW -> lastSin = muDoubleScalarSin ( _rtP -> P_76 *
ssGetTaskTime ( S , 1 ) ) ; _rtDW -> lastCos = muDoubleScalarCos ( _rtP ->
P_76 * ssGetTaskTime ( S , 1 ) ) ; _rtDW -> systemEnable = 0 ; }
rtb_B_11_68_0 = ( ( _rtDW -> lastSin * _rtP -> P_80 + _rtDW -> lastCos * _rtP
-> P_79 ) * _rtP -> P_78 + ( _rtDW -> lastCos * _rtP -> P_80 - _rtDW ->
lastSin * _rtP -> P_79 ) * _rtP -> P_77 ) * _rtP -> P_74 + _rtP -> P_75 ;
_rtB -> B_8_1_0 [ 0 ] = _rtB -> B_11_517_0 [ 0 ] * rtb_B_11_68_0 ; _rtB ->
B_8_1_0 [ 3 ] = _rtB -> B_11_48_0 [ 0 ] * rtb_B_11_68_0 ; _rtB -> B_8_1_0 [ 1
] = _rtB -> B_11_517_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_8_1_0 [ 4 ] = _rtB
-> B_11_48_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_8_1_0 [ 2 ] = _rtB ->
B_11_517_0 [ 2 ] * rtb_B_11_68_0 ; _rtB -> B_8_1_0 [ 5 ] = _rtB -> B_11_48_0
[ 2 ] * rtb_B_11_68_0 ; for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtDW ->
Integ4_SYSTEM_ENABLE_l != 0 ) { _rtB -> B_8_2_0 [ i ] = _rtDW ->
Integ4_DSTATE_b [ i ] ; } else { _rtB -> B_8_2_0 [ i ] = _rtP -> P_81 * _rtB
-> B_8_1_0 [ i ] + _rtDW -> Integ4_DSTATE_b [ i ] ; } } _rtB -> B_8_3_0 =
_rtP -> P_83 ; ssCallAccelRunBlock ( S , 8 , 4 , SS_CALL_MDL_OUTPUTS ) ; if (
ssGetTaskTime ( S , 1 ) >= _rtB -> B_8_3_0 ) { for ( i = 0 ; i < 6 ; i ++ ) {
_rtB -> B_8_11_0 [ i ] = ( _rtB -> B_8_2_0 [ i ] - _rtB -> B_8_4_0 [ i ] ) *
_rtP -> P_92 + ( _rtP -> P_72 * _rtB -> B_8_1_0 [ i ] - _rtP -> P_71 * _rtDW
-> UnitDelay_DSTATE_k [ i ] ) ; } } else { for ( i = 0 ; i < 6 ; i ++ ) {
_rtB -> B_8_11_0 [ i ] = _rtDW -> UnitDelay1_DSTATE_i [ i ] ; } } if ( _rtDW
-> systemEnable_p != 0 ) { _rtDW -> lastSin_a = muDoubleScalarSin ( _rtP ->
P_97 * ssGetTaskTime ( S , 1 ) ) ; _rtDW -> lastCos_j = muDoubleScalarCos (
_rtP -> P_97 * ssGetTaskTime ( S , 1 ) ) ; _rtDW -> systemEnable_p = 0 ; }
rtb_B_11_68_0 = ( ( _rtDW -> lastSin_a * _rtP -> P_101 + _rtDW -> lastCos_j *
_rtP -> P_100 ) * _rtP -> P_99 + ( _rtDW -> lastCos_j * _rtP -> P_101 - _rtDW
-> lastSin_a * _rtP -> P_100 ) * _rtP -> P_98 ) * _rtP -> P_95 + _rtP -> P_96
; _rtB -> B_8_13_0 [ 0 ] = _rtB -> B_11_517_0 [ 0 ] * rtb_B_11_68_0 ; _rtB ->
B_8_13_0 [ 3 ] = _rtB -> B_11_48_0 [ 0 ] * rtb_B_11_68_0 ; _rtB -> B_8_13_0 [
1 ] = _rtB -> B_11_517_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_8_13_0 [ 4 ] =
_rtB -> B_11_48_0 [ 1 ] * rtb_B_11_68_0 ; _rtB -> B_8_13_0 [ 2 ] = _rtB ->
B_11_517_0 [ 2 ] * rtb_B_11_68_0 ; _rtB -> B_8_13_0 [ 5 ] = _rtB -> B_11_48_0
[ 2 ] * rtb_B_11_68_0 ; for ( i = 0 ; i < 6 ; i ++ ) { if ( _rtDW ->
Integ4_SYSTEM_ENABLE_b != 0 ) { _rtB -> B_8_14_0 [ i ] = _rtDW ->
Integ4_DSTATE_o [ i ] ; } else { _rtB -> B_8_14_0 [ i ] = _rtP -> P_102 *
_rtB -> B_8_13_0 [ i ] + _rtDW -> Integ4_DSTATE_o [ i ] ; } } _rtB ->
B_8_15_0 = _rtP -> P_104 ; ssCallAccelRunBlock ( S , 8 , 16 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssGetTaskTime ( S , 1 ) >= _rtB -> B_8_15_0 ) {
for ( i = 0 ; i < 6 ; i ++ ) { _rtB -> B_8_23_0 [ i ] = ( _rtB -> B_8_14_0 [
i ] - _rtB -> B_8_16_0 [ i ] ) * _rtP -> P_113 + ( _rtP -> P_70 * _rtB ->
B_8_13_0 [ i ] - _rtP -> P_69 * _rtDW -> UnitDelay_DSTATE_c [ i ] ) ; } }
else { for ( i = 0 ; i < 6 ; i ++ ) { _rtB -> B_8_23_0 [ i ] = _rtDW ->
UnitDelay1_DSTATE_ip [ i ] ; } } for ( i = 0 ; i < 6 ; i ++ ) { _rtB ->
B_8_26_0 [ i ] = _rtP -> P_116 * muDoubleScalarHypot ( _rtB -> B_8_11_0 [ i ]
, _rtB -> B_8_23_0 [ i ] ) ; } if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( _rtDW -> RMS_SubsysRanBC ) ; } } for ( i = 0 ; i < 6 ; i ++ ) {
if ( _rtB -> B_11_540_0 ) { rtb_B_11_68_0 = _rtB -> B_10_12_0 [ i ] ; } else
{ rtb_B_11_68_0 = _rtB -> B_8_26_0 [ i ] ; } rtb_B_11_68_0 *= rtb_B_11_68_0 ;
if ( rtb_B_11_68_0 > _rtP -> P_271 ) { rtb_B_11_72_0 = _rtP -> P_271 ; } else
if ( rtb_B_11_68_0 < _rtP -> P_272 ) { rtb_B_11_72_0 = _rtP -> P_272 ; } else
{ rtb_B_11_72_0 = rtb_B_11_68_0 ; } rtb_B_11_68_0 = ( ( rtb_B_11_527_0 [ i ]
- rtb_B_11_538_0 [ i ] ) - rtb_B_11_68_0 ) / rtb_B_11_72_0 ; if (
rtb_B_11_68_0 > _rtP -> P_273 ) { rtb_B_11_68_0 = _rtP -> P_273 ; } else { if
( rtb_B_11_68_0 < _rtP -> P_274 ) { rtb_B_11_68_0 = _rtP -> P_274 ; } } _rtB
-> B_11_551_0 [ i ] = _rtP -> P_275 * muDoubleScalarSqrt ( rtb_B_11_68_0 ) ;
} ssCallAccelRunBlock ( S , 11 , 552 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 11 , 553 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_11_557_0 [ 0 ] = _rtP -> P_276 * _rtB -> B_11_13_0 [ 64 ] * _rtP -> P_279 ;
_rtB -> B_11_557_0 [ 1 ] = _rtP -> P_277 * _rtB -> B_11_13_0 [ 65 ] * _rtP ->
P_279 ; _rtB -> B_11_557_0 [ 2 ] = _rtP -> P_278 * _rtB -> B_11_13_0 [ 66 ] *
_rtP -> P_279 ; ssCallAccelRunBlock ( S , 11 , 558 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 11 , 630 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 11 , 631 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 11 , 632 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_11_638_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB ->
B_11_635_0 , _rtB -> B_11_634_0 ) , _rtP -> P_282 , _rtP -> P_281 , 2U ) ;
_rtB -> B_11_644_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_11_641_0 , _rtB -> B_11_640_0 ) , _rtP -> P_285 , _rtP -> P_284 , 2U ) ;
_rtB -> B_11_650_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_11_647_0 , _rtB -> B_11_646_0 ) , _rtP -> P_288 , _rtP -> P_287 , 2U ) ;
_rtB -> B_11_656_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_11_653_0 , _rtB -> B_11_652_0 ) , _rtP -> P_291 , _rtP -> P_290 , 2U ) ;
_rtB -> B_11_662_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_11_659_0 , _rtB -> B_11_658_0 ) , _rtP -> P_294 , _rtP -> P_293 , 2U ) ;
_rtB -> B_11_668_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB
-> B_11_665_0 , _rtB -> B_11_664_0 ) , _rtP -> P_297 , _rtP -> P_296 , 2U ) ;
i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_11_669_0 = _rtP
-> P_298 * _rtB -> B_11_64_0 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i !=
0 ) { rtb_B_11_68_0 = ( ( muDoubleScalarCos ( _rtB -> B_11_53_0 -
2.0943951023931953 ) * _rtB -> B_11_88_0 [ 1 ] + muDoubleScalarCos ( _rtB ->
B_11_53_0 ) * _rtB -> B_11_88_0 [ 0 ] ) + muDoubleScalarCos ( _rtB ->
B_11_53_0 + 2.0943951023931953 ) * _rtB -> B_11_88_0 [ 2 ] ) * _rtP -> P_299
; _rtB -> B_11_674_0 = _rtP -> P_300 * rtb_B_11_68_0 ; _rtB -> B_11_675_0 =
_rtP -> P_301 * _rtB -> B_11_674_0 + _rtDW -> Integrator_DSTATE_j ; _rtB ->
B_11_677_0 = _rtP -> P_303 * rtb_B_11_68_0 + _rtB -> B_11_675_0 ; } _rtB ->
B_11_681_0 = _rtB -> B_11_57_0 [ 0 ] - rtb_B_11_60_0 ; _rtB -> B_11_682_0 =
_rtB -> B_11_58_0 * _rtX -> Integrator2_CSTATE - _rtP -> P_304 *
rtb_B_11_60_0 ; _rtB -> B_11_686_0 = _rtB -> B_11_57_0 [ 1 ] - rtb_B_11_61_0
; _rtB -> B_11_687_0 = _rtB -> B_11_69_0 * _rtX -> Integrator2_CSTATE_f -
_rtP -> P_306 * rtb_B_11_61_0 ; _rtB -> B_11_691_0 = _rtB -> B_11_57_0 [ 2 ]
- rtb_B_11_75_0 ; _rtB -> B_11_692_0 = _rtB -> B_11_73_0 * _rtX ->
Integrator2_CSTATE_d - _rtP -> P_308 * rtb_B_11_75_0 ; i = ssIsSampleHit ( S
, 1 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 11 , 743 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_11_753_0 = _rtP -> P_311 * _rtB ->
B_11_13_0 [ 97 ] ; _rtB -> B_11_754_0 = _rtP -> P_312 * _rtB -> B_11_13_0 [
82 ] ; _rtB -> B_11_755_0 = _rtP -> P_313 * _rtB -> B_11_13_0 [ 76 ] ; _rtB
-> B_11_756_0 = _rtP -> P_314 * _rtB -> B_11_13_0 [ 77 ] ; _rtB -> B_11_757_0
= _rtP -> P_315 * _rtB -> B_11_13_0 [ 78 ] ; _rtB -> B_11_758_0 = _rtP ->
P_316 * _rtB -> B_11_13_0 [ 96 ] ; ssCallAccelRunBlock ( S , 11 , 759 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_11_760_0 = _rtX -> integ_CSTATE ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> T_PWORK . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> T_PWORK . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_318
; B_11_761_0 = control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> T_IWORK . CircularBufSize , & _rtDW
-> T_IWORK . Last , _rtDW -> T_IWORK . Tail , _rtDW -> T_IWORK . Head , _rtP
-> P_319 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_11_764_0 =
muDoubleScalarSqrt ( muDoubleScalarAbs ( _rtB -> B_11_760_0 - B_11_761_0 ) )
; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S ,
11 , 765 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_11_766_0 = _rtX ->
integrator_CSTATE ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_j . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_321 ; B_11_767_0 =
control_filtro_dq_mod21_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_h . CircularBufSize , &
_rtDW -> TransportDelay_IWORK_h . Last , _rtDW -> TransportDelay_IWORK_h .
Tail , _rtDW -> TransportDelay_IWORK_h . Head , _rtP -> P_322 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } _rtB -> B_11_769_0 = ( _rtB -> B_11_766_0 - B_11_767_0
) * _rtP -> P_323 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
ssCallAccelRunBlock ( S , 11 , 770 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_11_771_0 = _rtX -> integrator_CSTATE_l ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_a . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_a . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_325 ; B_11_772_0 = control_filtro_dq_mod21_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_ej
. CircularBufSize , & _rtDW -> TransportDelay_IWORK_ej . Last , _rtDW ->
TransportDelay_IWORK_ej . Tail , _rtDW -> TransportDelay_IWORK_ej . Head ,
_rtP -> P_326 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_11_774_0 = (
_rtB -> B_11_771_0 - B_11_772_0 ) * _rtP -> P_327 ; i = ssIsSampleHit ( S , 1
, 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 11 , 775 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 11 , 776 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_11_781_0 = _rtB -> B_11_754_0 * _rtB ->
B_11_754_0 * _rtP -> P_328 ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID3 ( SimStruct * S , int_T tid ) { B_control_filtro_dq_mod21_T *
_rtB ; P_control_filtro_dq_mod21_T * _rtP ; _rtP = ( (
P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_control_filtro_dq_mod21_T * ) _ssGetModelBlockIO ( S ) ) ; memcpy ( & _rtB
-> B_11_0_0 [ 0 ] , & _rtP -> P_136 [ 0 ] , sizeof ( real_T ) << 6U ) ; _rtB
-> B_11_1_0 = _rtP -> P_137 ; _rtB -> B_11_2_0 = _rtP -> P_138 ; _rtB ->
B_11_3_0 = _rtP -> P_139 ; _rtB -> B_11_4_0 = _rtP -> P_140 ; _rtB ->
B_11_5_0 = _rtP -> P_141 ; _rtB -> B_11_6_0 = _rtP -> P_142 ; _rtB ->
B_11_7_0 = _rtP -> P_143 ; _rtB -> B_11_8_0 = _rtP -> P_144 ; _rtB ->
B_11_9_0 = _rtP -> P_145 ; _rtB -> B_11_41_0 = _rtP -> P_171 ; _rtB ->
B_11_49_0 = _rtP -> P_178 ; _rtB -> B_11_58_0 = _rtP -> P_183 ; _rtB ->
B_11_62_0 = _rtP -> P_185 ; _rtB -> B_11_69_0 = _rtP -> P_190 ; _rtB ->
B_11_73_0 = _rtP -> P_192 ; _rtB -> B_11_168_0 = _rtP -> P_211 ; _rtB ->
B_11_170_0 = ! ( _rtB -> B_11_168_0 != 0.0 ) ; _rtB -> B_11_186_0 = _rtP ->
P_212 ; _rtB -> B_11_188_0 = ! ( _rtB -> B_11_186_0 != 0.0 ) ; _rtB ->
B_11_205_0 = _rtP -> P_214 ; _rtB -> B_11_207_0 = ! ( _rtB -> B_11_205_0 !=
0.0 ) ; _rtB -> B_11_229_0 = _rtP -> P_216 ; _rtB -> B_11_310_0 = _rtP ->
P_227 ; _rtB -> B_11_312_0 = ! ( _rtB -> B_11_310_0 != 0.0 ) ; _rtB ->
B_11_329_0 = _rtP -> P_229 ; _rtB -> B_11_331_0 = ! ( _rtB -> B_11_329_0 !=
0.0 ) ; _rtB -> B_11_348_0 = _rtP -> P_231 ; _rtB -> B_11_350_0 = ! ( _rtB ->
B_11_348_0 != 0.0 ) ; _rtB -> B_11_372_0 = _rtP -> P_233 ; _rtB -> B_11_453_0
= _rtP -> P_244 ; _rtB -> B_11_455_0 = ! ( _rtB -> B_11_453_0 != 0.0 ) ; _rtB
-> B_11_472_0 = _rtP -> P_246 ; _rtB -> B_11_474_0 = ! ( _rtB -> B_11_472_0
!= 0.0 ) ; _rtB -> B_11_491_0 = _rtP -> P_248 ; _rtB -> B_11_493_0 = ! ( _rtB
-> B_11_491_0 != 0.0 ) ; _rtB -> B_11_522_0 = ( _rtP -> P_255 != 0.0 ) ; _rtB
-> B_11_524_0 = ! _rtB -> B_11_522_0 ; _rtB -> B_11_540_0 = ( _rtP -> P_270
!= 0.0 ) ; _rtB -> B_11_542_0 = ! _rtB -> B_11_540_0 ; _rtB -> B_11_634_0 =
_rtP -> P_280 ; _rtB -> B_11_640_0 = _rtP -> P_283 ; _rtB -> B_11_646_0 =
_rtP -> P_286 ; _rtB -> B_11_652_0 = _rtP -> P_289 ; _rtB -> B_11_658_0 =
_rtP -> P_292 ; _rtB -> B_11_664_0 = _rtP -> P_295 ; _rtB -> B_11_742_0 =
_rtP -> P_310 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T HoldSine ;
int32_T i ; B_control_filtro_dq_mod21_T * _rtB ; P_control_filtro_dq_mod21_T
* _rtP ; DW_control_filtro_dq_mod21_T * _rtDW ; _rtDW = ( (
DW_control_filtro_dq_mod21_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_control_filtro_dq_mod21_T * ) _ssGetModelBlockIO ( S ) ) ; i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 11 ,
13 , SS_CALL_MDL_UPDATE ) ; _rtDW -> Integrator_DSTATE += _rtP -> P_181 *
_rtB -> B_11_677_0 ; _rtDW -> Integrator_PrevResetState = ( int8_T ) _rtB ->
B_11_50_0 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtDW ->
Integrator_DSTATE_l += _rtP -> P_188 * _rtB -> B_11_669_0 ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ]
; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK . Head < (
_rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_205 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_11_638_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_n . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_o . Head = ( ( _rtDW ->
TransportDelay_IWORK_o . Head < ( _rtDW -> TransportDelay_IWORK_o .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_o . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_o . Head == _rtDW ->
TransportDelay_IWORK_o . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_o . CircularBufSize , & _rtDW -> TransportDelay_IWORK_o
. Tail , & _rtDW -> TransportDelay_IWORK_o . Head , & _rtDW ->
TransportDelay_IWORK_o . Last , simTime - _rtP -> P_208 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_o .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_o . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_o . Head ] = _rtB ->
B_11_644_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_f . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_f . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_e . Head = ( ( _rtDW ->
TransportDelay_IWORK_e . Head < ( _rtDW -> TransportDelay_IWORK_e .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_e . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_e . Head == _rtDW ->
TransportDelay_IWORK_e . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_e . CircularBufSize , & _rtDW -> TransportDelay_IWORK_e
. Tail , & _rtDW -> TransportDelay_IWORK_e . Head , & _rtDW ->
TransportDelay_IWORK_e . Last , simTime - _rtP -> P_221 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_e .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_e . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_e . Head ] = _rtB ->
B_11_650_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_p . Head = ( ( _rtDW ->
TransportDelay_IWORK_p . Head < ( _rtDW -> TransportDelay_IWORK_p .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_p . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_p . Head == _rtDW ->
TransportDelay_IWORK_p . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_p . CircularBufSize , & _rtDW -> TransportDelay_IWORK_p
. Tail , & _rtDW -> TransportDelay_IWORK_p . Head , & _rtDW ->
TransportDelay_IWORK_p . Last , simTime - _rtP -> P_224 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_p .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_p . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_p . Head ] = _rtB ->
B_11_656_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_i . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_i . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_b . Head = ( ( _rtDW ->
TransportDelay_IWORK_b . Head < ( _rtDW -> TransportDelay_IWORK_b .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_b . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_b . Head == _rtDW ->
TransportDelay_IWORK_b . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_b . CircularBufSize , & _rtDW -> TransportDelay_IWORK_b
. Tail , & _rtDW -> TransportDelay_IWORK_b . Head , & _rtDW ->
TransportDelay_IWORK_b . Last , simTime - _rtP -> P_238 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_b .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_b . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_b . Head ] = _rtB ->
B_11_662_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_c . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_os . Head = ( ( _rtDW ->
TransportDelay_IWORK_os . Head < ( _rtDW -> TransportDelay_IWORK_os .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_os . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_os . Head == _rtDW ->
TransportDelay_IWORK_os . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_os . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_os . Tail , & _rtDW -> TransportDelay_IWORK_os . Head ,
& _rtDW -> TransportDelay_IWORK_os . Last , simTime - _rtP -> P_241 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_os . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_os . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_os . Head ] = _rtB -> B_11_668_0 ; } i = ssIsSampleHit (
S , 1 , 0 ) ; if ( i != 0 ) { if ( _rtDW -> TrueRMS_MODE_c ) { _rtDW ->
Integ4_SYSTEM_ENABLE_a = 0U ; for ( i = 0 ; i < 6 ; i ++ ) { _rtDW ->
Integ4_DSTATE_m [ i ] = _rtP -> P_53 * _rtB -> B_5_1_0 [ i ] + _rtB ->
B_5_2_0 [ i ] ; } ssCallAccelRunBlock ( S , 5 , 4 , SS_CALL_MDL_UPDATE ) ;
for ( i = 0 ; i < 6 ; i ++ ) { _rtDW -> UnitDelay_DSTATE_p [ i ] = _rtB ->
B_5_1_0 [ i ] ; _rtDW -> UnitDelay1_DSTATE_l [ i ] = _rtB -> B_5_10_0 [ i ] ;
} } if ( _rtDW -> RMS_MODE_i ) { HoldSine = _rtDW -> lastSin_o ; _rtDW ->
lastSin_o = _rtDW -> lastSin_o * _rtP -> P_11 + _rtDW -> lastCos_b * _rtP ->
P_10 ; _rtDW -> lastCos_b = _rtDW -> lastCos_b * _rtP -> P_11 - HoldSine *
_rtP -> P_10 ; _rtDW -> Integ4_SYSTEM_ENABLE_k = 0U ; for ( i = 0 ; i < 6 ; i
++ ) { _rtDW -> Integ4_DSTATE_h0 [ i ] = _rtP -> P_14 * _rtB -> B_3_1_0 [ i ]
+ _rtB -> B_3_2_0 [ i ] ; } ssCallAccelRunBlock ( S , 3 , 4 ,
SS_CALL_MDL_UPDATE ) ; HoldSine = _rtDW -> lastSin_k ; _rtDW -> lastSin_k =
_rtDW -> lastSin_k * _rtP -> P_32 + _rtDW -> lastCos_f * _rtP -> P_31 ; _rtDW
-> lastCos_f = _rtDW -> lastCos_f * _rtP -> P_32 - HoldSine * _rtP -> P_31 ;
_rtDW -> Integ4_SYSTEM_ENABLE_g = 0U ; for ( i = 0 ; i < 6 ; i ++ ) { _rtDW
-> UnitDelay_DSTATE_pe [ i ] = _rtB -> B_3_1_0 [ i ] ; _rtDW ->
UnitDelay1_DSTATE_n [ i ] = _rtB -> B_3_11_0 [ i ] ; _rtDW -> Integ4_DSTATE_l
[ i ] = _rtP -> P_35 * _rtB -> B_3_13_0 [ i ] + _rtB -> B_3_14_0 [ i ] ; }
ssCallAccelRunBlock ( S , 3 , 16 , SS_CALL_MDL_UPDATE ) ; for ( i = 0 ; i < 6
; i ++ ) { _rtDW -> UnitDelay_DSTATE_o [ i ] = _rtB -> B_3_13_0 [ i ] ; _rtDW
-> UnitDelay1_DSTATE_ib [ i ] = _rtB -> B_3_23_0 [ i ] ; } } _rtDW ->
Integ4_SYSTEM_ENABLE = 0U ; _rtDW -> Integ4_DSTATE [ 0 ] = _rtP -> P_256 *
_rtB -> B_11_517_0 [ 0 ] + _rtB -> B_11_528_0 [ 0 ] ; _rtDW -> Integ4_DSTATE
[ 3 ] = _rtP -> P_256 * _rtB -> B_11_48_0 [ 0 ] + _rtB -> B_11_528_0 [ 3 ] ;
_rtDW -> Integ4_DSTATE [ 1 ] = _rtP -> P_256 * _rtB -> B_11_517_0 [ 1 ] +
_rtB -> B_11_528_0 [ 1 ] ; _rtDW -> Integ4_DSTATE [ 4 ] = _rtP -> P_256 *
_rtB -> B_11_48_0 [ 1 ] + _rtB -> B_11_528_0 [ 4 ] ; _rtDW -> Integ4_DSTATE [
2 ] = _rtP -> P_256 * _rtB -> B_11_517_0 [ 2 ] + _rtB -> B_11_528_0 [ 2 ] ;
_rtDW -> Integ4_DSTATE [ 5 ] = _rtP -> P_256 * _rtB -> B_11_48_0 [ 2 ] + _rtB
-> B_11_528_0 [ 5 ] ; ssCallAccelRunBlock ( S , 11 , 530 , SS_CALL_MDL_UPDATE
) ; _rtDW -> UnitDelay_DSTATE [ 0 ] = _rtB -> B_11_517_0 [ 0 ] ; _rtDW ->
UnitDelay_DSTATE [ 3 ] = _rtB -> B_11_48_0 [ 0 ] ; _rtDW -> UnitDelay_DSTATE
[ 1 ] = _rtB -> B_11_517_0 [ 1 ] ; _rtDW -> UnitDelay_DSTATE [ 4 ] = _rtB ->
B_11_48_0 [ 1 ] ; _rtDW -> UnitDelay_DSTATE [ 2 ] = _rtB -> B_11_517_0 [ 2 ]
; _rtDW -> UnitDelay_DSTATE [ 5 ] = _rtB -> B_11_48_0 [ 2 ] ; for ( i = 0 ; i
< 6 ; i ++ ) { _rtDW -> UnitDelay1_DSTATE [ i ] = _rtB -> B_11_537_0 [ i ] ;
} if ( _rtDW -> TrueRMS_MODE ) { _rtDW -> Integ4_SYSTEM_ENABLE_n = 0U ; for (
i = 0 ; i < 6 ; i ++ ) { _rtDW -> Integ4_DSTATE_h [ i ] = _rtP -> P_120 *
_rtB -> B_10_1_0 [ i ] + _rtB -> B_10_2_0 [ i ] ; } ssCallAccelRunBlock ( S ,
10 , 4 , SS_CALL_MDL_UPDATE ) ; for ( i = 0 ; i < 6 ; i ++ ) { _rtDW ->
UnitDelay_DSTATE_a [ i ] = _rtB -> B_10_1_0 [ i ] ; _rtDW ->
UnitDelay1_DSTATE_g [ i ] = _rtB -> B_10_10_0 [ i ] ; } } if ( _rtDW ->
RMS_MODE ) { HoldSine = _rtDW -> lastSin ; _rtDW -> lastSin = _rtDW ->
lastSin * _rtP -> P_78 + _rtDW -> lastCos * _rtP -> P_77 ; _rtDW -> lastCos =
_rtDW -> lastCos * _rtP -> P_78 - HoldSine * _rtP -> P_77 ; _rtDW ->
Integ4_SYSTEM_ENABLE_l = 0U ; for ( i = 0 ; i < 6 ; i ++ ) { _rtDW ->
Integ4_DSTATE_b [ i ] = _rtP -> P_81 * _rtB -> B_8_1_0 [ i ] + _rtB ->
B_8_2_0 [ i ] ; } ssCallAccelRunBlock ( S , 8 , 4 , SS_CALL_MDL_UPDATE ) ;
HoldSine = _rtDW -> lastSin_a ; _rtDW -> lastSin_a = _rtDW -> lastSin_a *
_rtP -> P_99 + _rtDW -> lastCos_j * _rtP -> P_98 ; _rtDW -> lastCos_j = _rtDW
-> lastCos_j * _rtP -> P_99 - HoldSine * _rtP -> P_98 ; _rtDW ->
Integ4_SYSTEM_ENABLE_b = 0U ; for ( i = 0 ; i < 6 ; i ++ ) { _rtDW ->
UnitDelay_DSTATE_k [ i ] = _rtB -> B_8_1_0 [ i ] ; _rtDW ->
UnitDelay1_DSTATE_i [ i ] = _rtB -> B_8_11_0 [ i ] ; _rtDW -> Integ4_DSTATE_o
[ i ] = _rtP -> P_102 * _rtB -> B_8_13_0 [ i ] + _rtB -> B_8_14_0 [ i ] ; }
ssCallAccelRunBlock ( S , 8 , 16 , SS_CALL_MDL_UPDATE ) ; for ( i = 0 ; i < 6
; i ++ ) { _rtDW -> UnitDelay_DSTATE_c [ i ] = _rtB -> B_8_13_0 [ i ] ; _rtDW
-> UnitDelay1_DSTATE_ip [ i ] = _rtB -> B_8_23_0 [ i ] ; } } _rtDW ->
Integrator_DSTATE_j = _rtB -> B_11_675_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> T_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> T_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S )
; _rtDW -> T_IWORK . Head = ( ( _rtDW -> T_IWORK . Head < ( _rtDW -> T_IWORK
. CircularBufSize - 1 ) ) ? ( _rtDW -> T_IWORK . Head + 1 ) : 0 ) ; if (
_rtDW -> T_IWORK . Head == _rtDW -> T_IWORK . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> T_IWORK
. CircularBufSize , & _rtDW -> T_IWORK . Tail , & _rtDW -> T_IWORK . Head , &
_rtDW -> T_IWORK . Last , simTime - _rtP -> P_318 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> T_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> T_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
T_IWORK . Head ] = _rtB -> B_11_760_0 ; } { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 0 ] ; real_T * * tBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_h . Head = ( (
_rtDW -> TransportDelay_IWORK_h . Head < ( _rtDW -> TransportDelay_IWORK_h .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_h . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_h . Head == _rtDW ->
TransportDelay_IWORK_h . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_h . CircularBufSize , & _rtDW -> TransportDelay_IWORK_h
. Tail , & _rtDW -> TransportDelay_IWORK_h . Head , & _rtDW ->
TransportDelay_IWORK_h . Last , simTime - _rtP -> P_321 , tBuffer , uBuffer ,
( NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_h .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK_h . Head ] = _rtB ->
B_11_766_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_a . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_a . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_ej . Head = ( ( _rtDW ->
TransportDelay_IWORK_ej . Head < ( _rtDW -> TransportDelay_IWORK_ej .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_ej . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_ej . Head == _rtDW ->
TransportDelay_IWORK_ej . Tail ) { if ( !
control_filtro_dq_mod21_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_ej . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_ej . Tail , & _rtDW -> TransportDelay_IWORK_ej . Head ,
& _rtDW -> TransportDelay_IWORK_ej . Last , simTime - _rtP -> P_325 , tBuffer
, uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_ej . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_ej . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_ej . Head ] = _rtB -> B_11_771_0 ; } UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_control_filtro_dq_mod21_T *
_rtB ; XDot_control_filtro_dq_mod21_T * _rtXdot ; _rtXdot = ( (
XDot_control_filtro_dq_mod21_T * ) ssGetdX ( S ) ) ; _rtB = ( (
B_control_filtro_dq_mod21_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator1_CSTATE = _rtB -> B_11_682_0 ; _rtXdot -> Integrator1_CSTATE_n =
_rtB -> B_11_687_0 ; _rtXdot -> Integrator1_CSTATE_o = _rtB -> B_11_692_0 ;
_rtXdot -> Integrator2_CSTATE = _rtB -> B_11_681_0 ; _rtXdot ->
Integrator2_CSTATE_f = _rtB -> B_11_686_0 ; _rtXdot -> Integrator2_CSTATE_d =
_rtB -> B_11_691_0 ; _rtXdot -> integ_CSTATE = _rtB -> B_11_781_0 ; _rtXdot
-> integrator_CSTATE = _rtB -> B_11_754_0 ; _rtXdot -> integrator_CSTATE_l =
_rtB -> B_11_753_0 ; } static void mdlInitializeSizes ( SimStruct * S ) {
ssSetChecksumVal ( S , 0 , 726100881U ) ; ssSetChecksumVal ( S , 1 ,
2430920498U ) ; ssSetChecksumVal ( S , 2 , 3736933733U ) ; ssSetChecksumVal (
S , 3 , 4089755349U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "9.0" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_control_filtro_dq_mod21_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_control_filtro_dq_mod21_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_control_filtro_dq_mod21_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & control_filtro_dq_mod21_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T
) ) ; ( ( P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) -> P_67 =
rtInf ; ( ( P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) -> P_134 =
rtInf ; ( ( P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) -> P_271 =
rtInf ; ( ( P_control_filtro_dq_mod21_T * ) ssGetModelRtp ( S ) ) -> P_273 =
rtInf ; } static void mdlInitializeSampleTimes ( SimStruct * S ) {
slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
