/*********************** dSPACE target specific file *************************

   Header file smd_1202_sl_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1202 7.10 (02-May-2018)
   Sat Feb  9 12:10:58 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/
#ifndef RTI_HEADER_smd_1202_sl_trc_ptr_h_
#define RTI_HEADER_smd_1202_sl_trc_ptr_h_

/* Include the model header file. */
#include "smd_1202_sl.h"
#include "smd_1202_sl_private.h"
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
EXTERN_C volatile real_T *p_0_smd_1202_sl_real_T_0;
EXTERN_C volatile real_T *p_1_smd_1202_sl_real_T_0;
EXTERN_C volatile real_T *p_3_smd_1202_sl_real_T_0;

/*
 *  Declare the general function for TRC pointer initialization
 */
EXTERN_C void smd_1202_sl_rti_init_trc_pointers(void);

#endif                                 /* RTI_HEADER_smd_1202_sl_trc_ptr_h_ */
