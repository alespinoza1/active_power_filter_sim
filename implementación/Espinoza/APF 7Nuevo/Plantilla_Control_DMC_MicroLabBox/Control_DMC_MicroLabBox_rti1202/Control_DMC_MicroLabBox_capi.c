/*
 * Control_DMC_MicroLabBox_capi.c
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

#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Control_DMC_MicroLabBox_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "Control_DMC_MicroLabBox.h"
#include "Control_DMC_MicroLabBox_capi.h"
#include "Control_DMC_MicroLabBox_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING("contador"), 0, 0, 0, 0, 0 },

  { 1, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 1, 0, 1, 0, 0 },

  { 2, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 2, 0, 1, 0, 0 },

  { 3, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 3, 0, 2, 0, 0 },

  { 4, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 4, 0, 2, 0, 0 },

  { 5, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 5, 0, 2, 0, 0 },

  { 6, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 6, 0, 1, 0, 0 },

  { 7, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 7, 0, 1, 0, 0 },

  { 8, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Controlador"),
    TARGET_STRING(""), 8, 0, 3, 0, 0 },

  { 9, 0, TARGET_STRING("Control_DMC_MicroLabBox/Controlador/Transport Delay"),
    TARGET_STRING(""), 0, 0, 1, 0, 1 },

  { 10, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia1/NOT"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 11, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia1/NOT1"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 12, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia1/NOT2"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 13, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia1/NOT3"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 14, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia1/NOT4"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 15, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia1/NOT5"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 16, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Inversion  de  significancia2/NOT"),
    TARGET_STRING(""), 0, 1, 3, 0, 0 },

  { 17, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Mediciones1/S-Function Builder"),
    TARGET_STRING("IL_med"), 0, 0, 1, 0, 0 },

  { 18, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Mediciones1/S-Function Builder1"),
    TARGET_STRING("Vs_med"), 0, 0, 1, 0, 0 },

  { 19, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Mediciones1/S-Function Builder2"),
    TARGET_STRING("Ic_med"), 0, 0, 1, 0, 0 },

  { 20, 0, TARGET_STRING("Control_DMC_MicroLabBox/Subsystem/S-Function Builder1"),
    TARGET_STRING("Vec_SW"), 0, 0, 0, 0, 0 },

  { 21, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem1/S-Function Builder1"),
    TARGET_STRING("io"), 0, 0, 1, 0, 0 },

  { 22, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem2/S-Function Builder1"),
    TARGET_STRING("fc"), 0, 0, 1, 0, 0 },

  { 23, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem3/S-Function Builder1"),
    TARGET_STRING("icref"), 0, 0, 1, 0, 1 },

  { 24, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem4/S-Function Builder1"),
    TARGET_STRING("PLQL"), 0, 0, 2, 0, 0 },

  { 25, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem5/S-Function Builder1"),
    TARGET_STRING("ilalfabeta"), 0, 0, 2, 0, 0 },

  { 26, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem6/S-Function Builder1"),
    TARGET_STRING("vsalfabeta"), 0, 0, 2, 0, 0 },

  { 27, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem7/S-Function Builder1"),
    TARGET_STRING("ickm1"), 0, 0, 1, 0, 0 },

  { 28, 0, TARGET_STRING(
    "Control_DMC_MicroLabBox/Subsystem8/S-Function Builder1"),
    TARGET_STRING("bandera"), 0, 0, 3, 0, 0 },

  { 29, 0, TARGET_STRING("Control_DMC_MicroLabBox/TicTac/Gain"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 30, 0, TARGET_STRING("Control_DMC_MicroLabBox/TicTac/Sum"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 31, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/ILa/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 32, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/ILb /S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 33, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/ILc/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 34, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/Ica/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 35, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/Icb/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 36, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/Icc/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 37, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/Vsa/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 38, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/Vsb/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  { 39, 0, TARGET_STRING("Control_DMC_MicroLabBox/Mediciones1/Vsc/S-Function1"),
    TARGET_STRING(""), 0, 0, 3, 0, 0 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

#ifndef HOST_CAPI_BUILD

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &Control_DMC_MicroLabBox_B.contador[0],/* 0: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o2[0],/* 1: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o3[0],/* 2: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o4[0],/* 3: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o5[0],/* 4: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o6[0],/* 5: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o7[0],/* 6: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o8[0],/* 7: Signal */
  &Control_DMC_MicroLabBox_B.Controlador_o9,/* 8: Signal */
  &Control_DMC_MicroLabBox_B.TransportDelay[0],/* 9: Signal */
  &Control_DMC_MicroLabBox_B.NOT,      /* 10: Signal */
  &Control_DMC_MicroLabBox_B.NOT1,     /* 11: Signal */
  &Control_DMC_MicroLabBox_B.NOT2,     /* 12: Signal */
  &Control_DMC_MicroLabBox_B.NOT3,     /* 13: Signal */
  &Control_DMC_MicroLabBox_B.NOT4,     /* 14: Signal */
  &Control_DMC_MicroLabBox_B.NOT5,     /* 15: Signal */
  &Control_DMC_MicroLabBox_B.NOT_l,    /* 16: Signal */
  &Control_DMC_MicroLabBox_B.IL_med[0],/* 17: Signal */
  &Control_DMC_MicroLabBox_B.Vs_med[0],/* 18: Signal */
  &Control_DMC_MicroLabBox_B.Ic_med[0],/* 19: Signal */
  &Control_DMC_MicroLabBox_B.Vec_SW[0],/* 20: Signal */
  &Control_DMC_MicroLabBox_B.io[0],    /* 21: Signal */
  &Control_DMC_MicroLabBox_B.fc[0],    /* 22: Signal */
  &Control_DMC_MicroLabBox_B.icref[0], /* 23: Signal */
  &Control_DMC_MicroLabBox_B.PLQL[0],  /* 24: Signal */
  &Control_DMC_MicroLabBox_B.ilalfabeta[0],/* 25: Signal */
  &Control_DMC_MicroLabBox_B.vsalfabeta[0],/* 26: Signal */
  &Control_DMC_MicroLabBox_B.ickm1[0], /* 27: Signal */
  &Control_DMC_MicroLabBox_B.bandera,  /* 28: Signal */
  &Control_DMC_MicroLabBox_B.Gain,     /* 29: Signal */
  &Control_DMC_MicroLabBox_B.Sum,      /* 30: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_n,/* 31: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_o,/* 32: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_f,/* 33: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_j,/* 34: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_l,/* 35: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_ng,/* 36: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1,/* 37: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_h,/* 38: Signal */
  &Control_DMC_MicroLabBox_B.SFunction1_c,/* 39: Signal */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer */
  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0 },

  { "unsigned char", "boolean_T", 0, 0, sizeof(boolean_T), SS_BOOLEAN, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_VECTOR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 },

  { rtwCAPI_SCALAR, 6, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  6,                                   /* 0 */
  1,                                   /* 1 */
  3,                                   /* 2 */
  1,                                   /* 3 */
  2,                                   /* 4 */
  1,                                   /* 5 */
  1,                                   /* 6 */
  1                                    /* 7 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  1.0E-6, 0.0
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    1, 0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[1],
    0, 0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 40,
    (NULL), 0,
    (NULL), 0 },

  { (NULL), 0,
    (NULL), 0 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 3513275364U,
    1091285713U,
    1068024783U,
    861921423U },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  Control_DMC_MicroLabBox_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void Control_DMC_MicroLabBox_InitializeDataMapInfo(void)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(Control_DMC_MicroLabBox_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(Control_DMC_MicroLabBox_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(Control_DMC_MicroLabBox_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(Control_DMC_MicroLabBox_M->DataMapInfo.mmi,
    rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(Control_DMC_MicroLabBox_M->DataMapInfo.mmi,
    rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(Control_DMC_MicroLabBox_M->DataMapInfo.mmi,
    (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(Control_DMC_MicroLabBox_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(Control_DMC_MicroLabBox_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C" {

#endif

  void Control_DMC_MicroLabBox_host_InitializeDataMapInfo
    (Control_DMC_MicroLabBox_host_DataMapInfo_T *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* EOF: Control_DMC_MicroLabBox_capi.c */
