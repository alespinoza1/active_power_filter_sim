#ifndef RTW_HEADER_prueba02_cap_host_h_
#define RTW_HEADER_prueba02_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} prueba02_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void prueba02_host_InitializeDataMapInfo(prueba02_host_DataMapInfo_T *dataMap,
    const char *path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* RTW_HEADER_prueba02_cap_host_h_ */

/* EOF: prueba02_capi_host.h */
