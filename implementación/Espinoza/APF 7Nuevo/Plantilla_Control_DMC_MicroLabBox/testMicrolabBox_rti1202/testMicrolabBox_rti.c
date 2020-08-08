/*********************** dSPACE target specific file *************************

   Include file testMicrolabBox_rti.c:

   Definition of functions and variables for the system I/O and for
   the hardware and software interrupts used.

   RTI1202 7.10 (02-May-2018)
   Fri Mar 15 15:02:42 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

#if !(defined(__RTI_SIMENGINE__) || defined(RTIMP_FRAME))
# error This file may be included only by the RTI(-MP) simulation engine.
#endif

/* Include the model header file. */
#include "testMicrolabBox.h"
#include "testMicrolabBox_private.h"

/* Defines for block output and parameter structure existence */
#define RTI_rtB_STRUCTURE_EXISTS       1
#define RTI_rtP_STRUCTURE_EXISTS       1
#define RTB_STRUCTURE_NAME             testMicrolabBox_B
#define RTP_STRUCTURE_NAME             testMicrolabBox_P

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
AdcCl1AnalogInSDrvObject *pRTIAdcC1AnalogIn_Ch_2;
DacCl1AnalogOutSDrvObject *pRTIDacC1AnalogOut_Ch_2;
DacCl1AnalogOutSDrvObject *pRTIDacC1AnalogOut_Ch_1;
DioCl1DigInSDrvObject *pRTIDioC1DigIn_Port_2_Ch_16;
DioCl1DigOutSDrvObject *pRTIDioC1DigOut_Port_3_Ch_1;

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
static time_T dsTFinal = -1.0;

#define dsGetTFinal(rtm)               (dsTFinal)

static time_T dsStepSize = 0.0001;

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
  /* --- testMicrolabBox/ADC_CLASS1_BL1 --- */
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

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 */

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 Group:ADC */
  /* --- testMicrolabBox/ADC_CLASS1_BL1 --- */
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

  /* --- testMicrolabBox/DAC_CLASS1_BL1 --- */
  /* --- [RTI120X, DAC C1] - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init DAC CL1 AnalogOut driver object pRTIDacC1AnalogOut_Ch_2 */
    ioErrorCode = DacCl1AnalogOut_create(&pRTIDacC1AnalogOut_Ch_2,
      DAC_CLASS1_MASK_CH_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Apply all parameter settings. Finalize the construction of the AnalogOut driver object */
    ioErrorCode = DacCl1AnalogOut_apply(pRTIDacC1AnalogOut_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- testMicrolabBox/DAC_CLASS1_BL2 --- */
  /* --- [RTI120X, DAC C1] - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init DAC CL1 AnalogOut driver object pRTIDacC1AnalogOut_Ch_1 */
    ioErrorCode = DacCl1AnalogOut_create(&pRTIDacC1AnalogOut_Ch_1,
      DAC_CLASS1_MASK_CH_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Apply all parameter settings. Finalize the construction of the AnalogOut driver object */
    ioErrorCode = DacCl1AnalogOut_apply(pRTIDacC1AnalogOut_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- testMicrolabBox/DIO_CLASS1_BIT_IN_BL1 --- */
  /* --- [RTI120X, BITIN] - Port: 2 - Channel: 16 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* Init DIO CL1 DigIn driver object pRTIDioC1DigIn_Port_2_Ch_16 */
    ioErrorCode = DioCl1DigIn_create(&pRTIDioC1DigIn_Port_2_Ch_16,
      DIO_CLASS1_PORT_2, DIO_CLASS1_MASK_CH_16);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigIn_apply(pRTIDioC1DigIn_Port_2_Ch_16);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigIn_start(pRTIDioC1DigIn_Port_2_Ch_16);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- testMicrolabBox/DIO_CLASS1_BIT_OUT_BL1 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;

    /* Init DIO CL1 DigOut driver object pRTIDioC1DigOut_Port_3_Ch_1 */
    ioErrorCode = DioCl1DigOut_create(&pRTIDioC1DigOut_Port_3_Ch_1,
      DIO_CLASS1_PORT_3, DIO_CLASS1_MASK_CH_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_setSignalVoltage(pRTIDioC1DigOut_Port_3_Ch_1,
      DIO_CLASS1_SIGNAL_5_0_V);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (1 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 1-1 on port 3 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_3_Ch_1,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_apply(pRTIDioC1DigOut_Port_3_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_start(pRTIDioC1DigOut_Port_3_Ch_1);
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
  /* --- testMicrolabBox/DAC_CLASS1_BL1 --- */
  /* --- [RTI120X, DAC C1] - Channel: 2 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* All channel outputs are released from high impedance state */
    DacCl1AnalogOut_setOutputHighZ(pRTIDacC1AnalogOut_Ch_2,
      DAC_CLASS1_HIGH_Z_OFF);

    /* write initial value of CL1 DAC for output channel 2 */
    ioErrorCode = DacCl1AnalogOut_setOutputValue(pRTIDacC1AnalogOut_Ch_2,
      DAC_CLASS1_CHANNEL_2, (Float64) 0.0);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Activates AnalogOut functionality */
    ioErrorCode = DacCl1AnalogOut_start(pRTIDacC1AnalogOut_Ch_2);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- testMicrolabBox/DAC_CLASS1_BL2 --- */
  /* --- [RTI120X, DAC C1] - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* All channel outputs are released from high impedance state */
    DacCl1AnalogOut_setOutputHighZ(pRTIDacC1AnalogOut_Ch_1,
      DAC_CLASS1_HIGH_Z_OFF);

    /* write initial value of CL1 DAC for output channel 1 */
    ioErrorCode = DacCl1AnalogOut_setOutputValue(pRTIDacC1AnalogOut_Ch_1,
      DAC_CLASS1_CHANNEL_1, (Float64) 0.0);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    /* Activates AnalogOut functionality */
    ioErrorCode = DacCl1AnalogOut_start(pRTIDacC1AnalogOut_Ch_1);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }
  }

  /* --- testMicrolabBox/DIO_CLASS1_BIT_OUT_BL1 --- */
  /* --- [RTI120X, BITOUT] - Port: 3 - Channel: 1 --- */
  {
    /* define a variable for IO error handling */
    UInt32 ioErrorCode = IOLIB_NO_ERROR;

    /* define variables required for BitOut initial functions */
    UInt32 outputDataInit = 0;
    ioErrorCode = DioCl1DigOut_setChMaskOutHighZ(pRTIDioC1DigOut_Port_3_Ch_1,
      DIO_CLASS1_HIGH_Z_OFF);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    outputDataInit = ( ( ( (UInt32)0) << (1 - 1)) | outputDataInit);

    /* write initialization value to digital output channel 1-1 on port 3 */
    ioErrorCode = DioCl1DigOut_setChMaskOutData(pRTIDioC1DigOut_Port_3_Ch_1,
      outputDataInit);
    if (ioErrorCode > IOLIB_NO_ERROR) {
      RTLIB_EXIT(1);
    }

    ioErrorCode = DioCl1DigOut_write(pRTIDioC1DigOut_Port_3_Ch_1);
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
  /* Calls for base sample time: [0.0001, 0.0] */
  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 */

  /* dSPACE I/O Board DS120XSTDADCC1 #0 Unit:ADCC1 Group:ADC */
  /* fire burst- or conversion trigger for analog input channel. Called by ADC C1 block pRTIAdcC1AnalogIn_Ch_2 */
  AdcCl1AnalogIn_setConversSwTrigger(pRTIAdcC1AnalogIn_Ch_2);
  AdcCl1AnalogIn_write(pRTIAdcC1AnalogIn_Ch_2);

  /* --- testMicrolabBox/DIO_CLASS1_BIT_IN_BL1 --- */
  /* --- [RTI120X, BITIN] - Port: 2 - Channel: 16 --- */
  {
    UInt32 inputDataUInt32;

    /* get digital signal state on channel 16-16 on port 2 */
    DioCl1DigIn_read(pRTIDioC1DigIn_Port_2_Ch_16);
    DioCl1DigIn_getChMaskInData(pRTIDioC1DigIn_Port_2_Ch_16, &inputDataUInt32);
    testMicrolabBox_B.SFunction1_e = (boolean_T)((inputDataUInt32 &
      DIO_CLASS1_MASK_CH_16) >> 15);
  }
}

static void rti_mdl_daq_service()
{
  /* dSPACE Host Service */
  DsDaq_Service(0, 0, 1, (DsDaqSTimestampStruct *)
                rtk_current_task_absolute_time_ptr_get());
}

#undef __INLINE

/****** [EOF] ****************************************************************/
