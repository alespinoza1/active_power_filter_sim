/*********************** dSPACE target specific file *************************

   Header file testMicrolabBox_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1202 7.10 (02-May-2018)
   Fri Mar 15 15:02:42 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/
#ifndef RTI_HEADER_testMicrolabBox_trc_ptr_h_
#define RTI_HEADER_testMicrolabBox_trc_ptr_h_

/* Include the model header file. */
#include "testMicrolabBox.h"
#include "testMicrolabBox_private.h"
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
EXTERN_C volatile real_T *p_0_testMicrolabBox_real_T_0;
EXTERN_C volatile boolean_T *p_0_testMicrolabBox_boolean_T_1;
EXTERN_C volatile real_T *p_1_testMicrolabBox_real_T_0;

/*
 *  Declare the general function for TRC pointer initialization
 */
EXTERN_C void testMicrolabBox_rti_init_trc_pointers(void);

#endif                                 /* RTI_HEADER_testMicrolabBox_trc_ptr_h_ */
