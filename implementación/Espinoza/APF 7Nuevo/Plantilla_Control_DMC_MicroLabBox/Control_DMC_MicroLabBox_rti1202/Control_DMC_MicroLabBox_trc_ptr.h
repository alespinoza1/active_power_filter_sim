/*********************** dSPACE target specific file *************************

   Header file Control_DMC_MicroLabBox_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1202 7.10 (02-May-2018)
   Fri Jun  7 14:46:00 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/
#ifndef RTI_HEADER_Control_DMC_MicroLabBox_trc_ptr_h_
#define RTI_HEADER_Control_DMC_MicroLabBox_trc_ptr_h_

/* Include the model header file. */
#include "Control_DMC_MicroLabBox.h"
#include "Control_DMC_MicroLabBox_private.h"
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
EXTERN_C volatile real_T *p_0_Control_DMC_MicroLabBox_real_T_0;
EXTERN_C volatile boolean_T *p_0_Control_DMC_MicroLabBox_boolean_T_1;
EXTERN_C volatile real_T *p_1_Control_DMC_MicroLabBox_real_T_0;
EXTERN_C volatile real_T *p_2_Control_DMC_MicroLabBox_real_T_0;
EXTERN_C volatile int_T *p_2_Control_DMC_MicroLabBox_int_T_2;

/*
 *  Declare the general function for TRC pointer initialization
 */
EXTERN_C void Control_DMC_MicroLabBox_rti_init_trc_pointers(void);

#endif                                 /* RTI_HEADER_Control_DMC_MicroLabBox_trc_ptr_h_ */
