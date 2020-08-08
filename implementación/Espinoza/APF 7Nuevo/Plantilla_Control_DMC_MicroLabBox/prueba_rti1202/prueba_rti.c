/*********************** dSPACE target specific file *************************

   Include file prueba_rti.c:

   Definition of functions and variables for the system I/O and for
   the hardware and software interrupts used.

   RTI1202 7.10 (02-May-2018)
   Tue Apr 16 10:06:45 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

#if !(defined(__RTI_SIMENGINE__) || defined(RTIMP_FRAME))
# error This file may be included only by the RTI(-MP) simulation engine.
#endif

/* Include the model header file. */
#include "prueba.h"
#include "prueba_private.h"

/* Defines for block output and parameter structure existence */
#define RTI_rtB_STRUCTURE_EXISTS       1
#define RTI_rtP_STRUCTURE_EXISTS       0
#define RTB_STRUCTURE_NAME             prueba_B

/* dSPACE generated includes for header files */
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#ifndef dsRtmGetNumSampleTimes
# define dsRtmGetNumSampleTimes(rtm)   1
#endif

#ifndef dsRtmSetTaskTime
#define dsRtmSetTaskTime(rtm, sti, val) (((rtm)->Timing.taskTime0) = (val))
#endif

/****** Definitions: task functions for timer tasks *********************/

/* Timer Task 1. (Base rate). */
static void rti_TIMERA(rtk_p_task_control_block task)
{
  /* Task entry code BEGIN */
  /* -- None. -- */
  /* Task entry code END */

  /* Task code. */
  baseRateService(task);

  /* Task exit code BEGIN */
  /* -- None. -- */
  /* Task exit code END */
}

/* ===== Declarations of RTI blocks ======================================== */
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_1;

/* ===== Definition of interface functions for simulation engine =========== */
#if GRTINTERFACE == 1
#ifdef MULTITASKING
# define dsIsSampleHit(RTM,sti)        rtmGetSampleHitPtr(RTM)[sti]
#else
# define dsIsSampleHit(RTM,sti)        1
#endif

#else
#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

# define dsIsSampleHit(RTM,sti)        rtmStepTask(RTM, sti)
#endif

#undef __INLINE
#if defined(_INLINE)
# define __INLINE                      static inline
#else
# define __INLINE                      static
#endif

/*Define additional variables*/
static time_T dsTFinal = 10.0;

#define dsGetTFinal(rtm)               (dsTFinal)

static time_T dsStepSize = 1.0E-6;

# define dsGetStepSize(rtm)            (dsStepSize)

static void rti_mdl_initialize_host_services(void)
{
  DsDaq_Init(0, 32, 1);
}

static void rti_mdl_initialize_io_boards(void)
{
  /* Registering of RTI products and modules at VCM */
  {
    vcm_module_register(VCM_MID_RTI1202, (void *) 0,
                        VCM_TXT_RTI1202, 7, 10, 0,
                        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);

    {
      vcm_module_descriptor_type* msg_mod_ptr;
      msg_mod_ptr = vcm_module_register(VCM_MID_MATLAB, (void *) 0,
        VCM_TXT_MATLAB, 9, 5, 0,
        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_SIMULINK, msg_mod_ptr,
                          VCM_TXT_SIMULINK, 9, 2, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_RTW, msg_mod_ptr,
                          VCM_TXT_RTW, 9, 0, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
    }
  }

  /* dSPACE I/O Board DS120XSTDADCC1 #0 */
  /* --- prueba/ADC_CLASS1_BL1 --- */
  /* --- [RTI120X, ADC C1] - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_1 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_1,
      ADC_CLASS1_CHANNEL_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_1 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_1,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_1,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 */

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 Group:ADC */
  /* --- prueba/ADC_CLASS1_BL1 --- */
  /* --- [RTI120X, ADC C1] - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_1 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }
}

/* Function rti_mdl_slave_load() is empty */
#define rti_mdl_slave_load()

/* Function rti_mdl_rtk_initialize() is empty */
#define rti_mdl_rtk_initialize()

/* Function rti_mdl_initialize_io_units() is empty */
#define rti_mdl_initialize_io_units()

/* Function rti_mdl_acknowledge_interrupts() is empty */
#define rti_mdl_acknowledge_interrupts()

/* Function rti_mdl_timetables_register() is empty */
#define rti_mdl_timetables_register()

/* Function rti_mdl_timesync_simstate() is empty */
#define rti_mdl_timesync_simstate()

/* Function rti_mdl_timesync_baserate() is empty */
#define rti_mdl_timesync_baserate()

static void rti_mdl_background(void)
{
  /* DsDaq background call */
  DsDaq_Background(0);
}

__INLINE void rti_mdl_sample_input(void)
{
  /* Calls for base sample time: [1.0E-6, 0.0] */
  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 */

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 Group:ADC */
  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_1 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_1);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_1);
}

static void rti_mdl_daq_service()
{
  /* dSPACE Host Service */
  DsDaq_Service(0, 0, 1, (DsDaqSTimestampStruct *)
                rtk_current_task_absolute_time_ptr_get());
}

#undef __INLINE

/****** [EOF] ****************************************************************/
