/***************************************************************************

   Source file Control_APF7_MicroLabBox_trc_ptr.c:

   Definition of function that initializes the global TRC pointers

   RTI1202 7.10 (02-May-2018)
   Fri Jul 24 16:44:51 2020

   Copyright 2020, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

/* Include header file. */
#include "Control_APF7_MicroLabBox_trc_ptr.h"
#include "Control_APF7_MicroLabBox.h"
#include "Control_APF7_MicroLabBox_private.h"

/* Compiler options to turn off optimization. */
#if !defined(DS_OPTIMIZE_INIT_TRC_POINTERS)
#ifdef _MCCPPC

#pragma options -nOt -nOr -nOi -nOx

#endif

#ifdef __GNUC__

#pragma GCC optimize ("O0")

#endif

#ifdef _MSC_VER

#pragma optimize ("", off)

#endif
#endif

/* Definition of Global pointers to data type transitions (for TRC-file access) */
volatile real_T *p_0_Control_APF7_MicroLabBox_real_T_0 = NULL;
volatile boolean_T *p_0_Control_APF7_MicroLabBox_boolean_T_1 = NULL;
volatile real_T *p_1_Control_APF7_MicroLabBox_real_T_0 = NULL;
volatile real_T *p_2_Control_APF7_MicroLabBox_real_T_0 = NULL;
volatile int_T *p_2_Control_APF7_MicroLabBox_int_T_2 = NULL;

/*
 *  Declare the functions, that initially assign TRC pointers
 */
static void rti_init_trc_pointers_0(void);

/* Global pointers to data type transitions are separated in different functions to avoid overloading */
static void rti_init_trc_pointers_0(void)
{
  p_0_Control_APF7_MicroLabBox_real_T_0 = &Control_APF7_MicroLabBox_B.Gain;
  p_0_Control_APF7_MicroLabBox_boolean_T_1 = &Control_APF7_MicroLabBox_B.NOT4;
  p_1_Control_APF7_MicroLabBox_real_T_0 =
    &Control_APF7_MicroLabBox_P.Ganancia_Ica;
  p_2_Control_APF7_MicroLabBox_real_T_0 =
    &Control_APF7_MicroLabBox_DW.Memory_PreviousInput;
  p_2_Control_APF7_MicroLabBox_int_T_2 =
    &Control_APF7_MicroLabBox_DW.TransportDelay_IWORK.Tail;
}

void Control_APF7_MicroLabBox_rti_init_trc_pointers(void)
{
  rti_init_trc_pointers_0();
}
