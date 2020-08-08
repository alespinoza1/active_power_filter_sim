/***************************************************************************

   Source file testMicrolabBox_trc_ptr.c:

   Definition of function that initializes the global TRC pointers

   RTI1202 7.10 (02-May-2018)
   Fri Mar 15 15:02:42 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

/* Include header file. */
#include "testMicrolabBox_trc_ptr.h"
#include "testMicrolabBox.h"
#include "testMicrolabBox_private.h"

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
volatile real_T *p_0_testMicrolabBox_real_T_0 = NULL;
volatile boolean_T *p_0_testMicrolabBox_boolean_T_1 = NULL;
volatile real_T *p_1_testMicrolabBox_real_T_0 = NULL;

/*
 *  Declare the functions, that initially assign TRC pointers
 */
static void rti_init_trc_pointers_0(void);

/* Global pointers to data type transitions are separated in different functions to avoid overloading */
static void rti_init_trc_pointers_0(void)
{
  p_0_testMicrolabBox_real_T_0 = &testMicrolabBox_B.SFunction1;
  p_0_testMicrolabBox_boolean_T_1 = &testMicrolabBox_B.SFunction1_e;
  p_1_testMicrolabBox_real_T_0 = &testMicrolabBox_P.Constant_Value;
}

void testMicrolabBox_rti_init_trc_pointers(void)
{
  rti_init_trc_pointers_0();
}
