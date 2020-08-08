/*********************** dSPACE target specific file *************************

   Include file Control_DMC_MicroLabBox_rti.c:

   Definition of functions and variables for the system I/O and for
   the hardware and software interrupts used.

   RTI1202 7.10 (02-May-2018)
   Fri Jun  7 14:46:00 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

#if !(defined(__RTI_SIMENGINE__) || defined(RTIMP_FRAME))
# error This file may be included only by the RTI(-MP) simulation engine.
#endif

/* Include the model header file. */
#include "Control_DMC_MicroLabBox.h"
#include "Control_DMC_MicroLabBox_private.h"

/* Defines for block output and parameter structure existence */
#define RTI_rtB_STRUCTURE_EXISTS       1
#define RTI_rtP_STRUCTURE_EXISTS       1
#define RTB_STRUCTURE_NAME             Control_DMC_MicroLabBox_B
#define RTP_STRUCTURE_NAME             Control_DMC_MicroLabBox_P

/* dSPACE generated includes for header files */
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#ifndef dsRtmGetNumSampleTimes
# define dsRtmGetNumSampleTimes(rtm)   4
#endif

#ifndef dsRtmGetTPtr
# define dsRtmGetTPtr(rtm)             ((rtm)->Timing.t)
#endif

#ifndef dsRtmSetTaskTime
# define dsRtmSetTaskTime(rtm, sti, val) (dsRtmGetTPtr((rtm))[sti] = (val))
#endif

/****** Definitions: task functions for timer tasks *********************/

/* Timer Task 1. (Base rate). */
static void rti_120XDIOCL1PWM_FALLING_EDGEP3Ch1(rtk_p_task_control_block task)
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
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_2;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_3;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_9;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_10;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_11;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_17;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_18;
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_19;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_12;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_11;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_3;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_1_Ch_2;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_4;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_2_Ch_2;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_3_Ch_3;
DioCl1PwmOutSDrvObject *pRTIDioC1PwmOut_Port_3_Ch_1;

/* ===== Definition of interface functions for simulation engine =========== */
#if GRTINTERFACE == 1
#ifdef MULTITASKING
# define dsIsSampleHit(RTM,sti)        rtmGetSampleHitPtr(RTM)[sti]
#else
# define dsIsSampleHit(RTM,sti)        rtmIsSampleHit(RTM,sti,0)
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
static time_T dsTFinal = -1.0;

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
  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsa --- */
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

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsb --- */
  /* --- [RTI120X, ADC C1] - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_2 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_2,
      ADC_CLASS1_CHANNEL_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_2 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_2,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_2,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsc --- */
  /* --- [RTI120X, ADC C1] - Channel: 3 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_3 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_3,
      ADC_CLASS1_CHANNEL_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_3 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_3,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_3,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILa --- */
  /* --- [RTI120X, ADC C1] - Channel: 9 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_9 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_9,
      ADC_CLASS1_CHANNEL_9);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_9 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_9,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_9,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILb  --- */
  /* --- [RTI120X, ADC C1] - Channel: 10 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_10 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_10,
      ADC_CLASS1_CHANNEL_10);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_10 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_10,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_10,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILc --- */
  /* --- [RTI120X, ADC C1] - Channel: 11 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_11 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_11,
      ADC_CLASS1_CHANNEL_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_11 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_11,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_11,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Ica --- */
  /* --- [RTI120X, ADC C1] - Channel: 17 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_17 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_17,
      ADC_CLASS1_CHANNEL_17);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_17 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_17,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_17,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Icb --- */
  /* --- [RTI120X, ADC C1] - Channel: 18 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_18 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_18,
      ADC_CLASS1_CHANNEL_18);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_18 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_18,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_18,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Icc --- */
  /* --- [RTI120X, ADC C1] - Channel: 19 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_19 */
    ioErrorCode = AdcCl1AnalogIn_create(&pRTIAdcC1AnalogIn_Ch_19,
      ADC_CLASS1_CHANNEL_19);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Set parameters for ADC CL1 AnalogIn driver object pRTIAdcC1AnalogIn_Ch_19 */
    ioErrorCode = AdcCl1AnalogIn_setConversionMode(pRTIAdcC1AnalogIn_Ch_19,
      ADC_CLASS1_SINGLE_CONV_MODE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_setConversTrigger(pRTIAdcC1AnalogIn_Ch_19,
      ADC_CLASS1_TRIGGER_SW);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 */

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 Group:ADC */
  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsa --- */
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

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsb --- */
  /* --- [RTI120X, ADC C1] - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_2 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Vsc --- */
  /* --- [RTI120X, ADC C1] - Channel: 3 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_3 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILa --- */
  /* --- [RTI120X, ADC C1] - Channel: 9 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_9 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_9);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_9);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILb  --- */
  /* --- [RTI120X, ADC C1] - Channel: 10 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_10 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_10);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_10);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/ILc --- */
  /* --- [RTI120X, ADC C1] - Channel: 11 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_11 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Ica --- */
  /* --- [RTI120X, ADC C1] - Channel: 17 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_17 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_17);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_17);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Icb --- */
  /* --- [RTI120X, ADC C1] - Channel: 18 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_18 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_18);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_18);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Mediciones1/Icc --- */
  /* --- [RTI120X, ADC C1] - Channel: 19 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Apply- and Start-Fcn for pRTIAdcC1AnalogIn_Ch_19 */
    ioErrorCode = AdcCl1AnalogIn_apply(pRTIAdcC1AnalogIn_Ch_19);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = AdcCl1AnalogIn_start(pRTIAdcC1AnalogIn_Ch_19);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 12 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_1_Ch_12 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_1_Ch_12,
      DIO_CLASS1_PORT_1, DIO_CLASS1_MASK_CH_12);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_1_Ch_12,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (12 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 12-12 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_12,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_1_Ch_12);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_1_Ch_12);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF1 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 11 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_1_Ch_11 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_1_Ch_11,
      DIO_CLASS1_PORT_1, DIO_CLASS1_MASK_CH_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_1_Ch_11,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (11 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 11-11 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_11,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_1_Ch_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_1_Ch_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF2 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 3 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_1_Ch_3 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_1_Ch_3,
      DIO_CLASS1_PORT_1, DIO_CLASS1_MASK_CH_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_1_Ch_3,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (3 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 3-3 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_3,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_1_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_1_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF3 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_1_Ch_2 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_1_Ch_2,
      DIO_CLASS1_PORT_1, DIO_CLASS1_MASK_CH_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_1_Ch_2,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (2 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 2-2 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_2,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_1_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_1_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF4 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 4 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_2_Ch_4 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_2_Ch_4,
      DIO_CLASS1_PORT_2, DIO_CLASS1_MASK_CH_4);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_2_Ch_4,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (4 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 4-4 on port 2 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_4,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_2_Ch_4);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_2_Ch_4);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_2_Ch_2 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_2_Ch_2,
      DIO_CLASS1_PORT_2, DIO_CLASS1_MASK_CH_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_2_Ch_2,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (2 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 2-2 on port 2 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_2,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_2_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_2_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 3 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_3_Ch_3 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_3_Ch_3,
      DIO_CLASS1_PORT_3, DIO_CLASS1_MASK_CH_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_3_Ch_3,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (3 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 3-3 on port 3 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_3_Ch_3,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_3_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_3_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/DIO_CLASS1_PWM_BL1 --- */
  /* --- [RTI120X, PWM OUT] - Port: 3 - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init DIO CL1 PwmOut driver object pRTIDioC1PwmOut_Port_3_Ch_1 */
    ioErrorCode = DioCl1PwmOut_create(&pRTIDioC1PwmOut_Port_3_Ch_1,
      DIO_CLASS1_PORT_3, DIO_CLASS1_CHANNEL_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setSignalVoltage(pRTIDioC1PwmOut_Port_3_Ch_1,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setUpdateMode(pRTIDioC1PwmOut_Port_3_Ch_1,
      DIO_PWM_SYNC_UPDATE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setInvertingMode(pRTIDioC1PwmOut_Port_3_Ch_1,
      DIO_CLASS1_NOT_INVERTED);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setInterruptMode(pRTIDioC1PwmOut_Port_3_Ch_1,
      DIO_CLASS1_INT_FALLING_EDGE);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setEventDownsample(pRTIDioC1PwmOut_Port_3_Ch_1, 1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setEventDelay(pRTIDioC1PwmOut_Port_3_Ch_1, 0);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setPeriod(pRTIDioC1PwmOut_Port_3_Ch_1, 5.0E-5);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setDutyCycle(pRTIDioC1PwmOut_Port_3_Ch_1, 0.5);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_apply(pRTIDioC1PwmOut_Port_3_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_start(pRTIDioC1PwmOut_Port_3_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }
}

/* Function rti_mdl_slave_load() is empty */
#define rti_mdl_slave_load()

/* Function rti_mdl_rtk_initialize() is empty */
#define rti_mdl_rtk_initialize()

static void rti_mdl_initialize_io_units(void)
{
  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 12 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_12,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (12 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 12-12 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_12,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_12);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF1 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 11 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_11,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (11 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 11-11 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_11,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_11);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF2 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 3 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_3,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (3 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 3-3 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_3,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF3 --- */
  /* --- [RTI120X, BITOUT] - Port: 1 - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_1_Ch_2,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (2 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 2-2 on port 1 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_1_Ch_2,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_1_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF4 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 4 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_4,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (4 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 4-4 on port 2 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_4,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_4);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 2 - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_2_Ch_2,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (2 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 2-2 on port 2 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_2_Ch_2,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_2_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/Señales de Conmutación  APF5 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 3 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_3_Ch_3,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (3 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 3-3 on port 3 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_3_Ch_3,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_3_Ch_3);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- Control_DMC_MicroLabBox/DIO_CLASS1_PWM_BL1 --- */
  /* --- [RTI120X, PWM OUT] - Port: 3 - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;
    ioErrorCode = DioCl1PwmOut_setOutputHighZ(pRTIDioC1PwmOut_Port_3_Ch_1,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* write initial values of PWM Period and DutyCycle for output channel 1 on port 3 */
    ioErrorCode = DioCl1PwmOut_setPeriod(pRTIDioC1PwmOut_Port_3_Ch_1, 5.0E-5);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_setDutyCycle(pRTIDioC1PwmOut_Port_3_Ch_1, 0.5);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1PwmOut_write(pRTIDioC1PwmOut_Port_3_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }
}

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
  /* Calls for base sample time: [1.0E-6, 0] */
  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 */

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 Group:ADC */
  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_1 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_1);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_1);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_2 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_2);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_2);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_3 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_3);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_3);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_9 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_9);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_9);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_10 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_10);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_10);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_11 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_11);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_11);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_17 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_17);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_17);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_18 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_18);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_18);

  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_19 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_19);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_19);
}

static void rti_mdl_daq_service()
{
  /* dSPACE Host Service */
  DsDaq_Service(0, 0, 1, (DsDaqSTimestampStruct *)
                rtk_current_task_absolute_time_ptr_get());
}

#undef __INLINE

/****** [EOF] ****************************************************************/
