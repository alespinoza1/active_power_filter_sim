  /*********************** dSPACE target specific file *************************

   Header file prueba01_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1202 7.10 (02-May-2018)
   Tue Apr 16 10:01:03 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

  *****************************************************************************/
  #ifndef RTI_HEADER_prueba01_trc_ptr_h_
  #define RTI_HEADER_prueba01_trc_ptr_h_
  /* Include the model header file. */
  #include "prueba01.h"
  #include "prueba01_private.h"

  #ifdef EXTERN_C
  #undef EXTERN_C
  #endif

  #ifdef __cplusplus
  #define EXTERN_C                       extern "C"
  #else
  #define EXTERN_C                       extern
  #endif

  /*
   *  Declare the global TRC pointers
   */
              EXTERN_C volatile  real_T *p_0_prueba01_real_T_0;

  /*
   *  Declare the general function for TRC pointer initialization
   */
  EXTERN_C void prueba01_rti_init_trc_pointers(void);
   #endif                       /* RTI_HEADER_prueba01_trc_ptr_h_ */
