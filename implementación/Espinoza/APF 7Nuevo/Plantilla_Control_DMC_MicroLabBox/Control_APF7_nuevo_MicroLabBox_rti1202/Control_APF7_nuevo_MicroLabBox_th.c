/************************ dSPACE target specific file *************************

   Include file .\Control_APF7_nuevo_MicroLabBox_rti1202\Control_APF7_nuevo_MicroLabBox_th.c :

   Task Configuration file for model : Control_APF7_nuevo_MicroLabBox

   RTI1202 7.10 (02-May-2018)/2.17
   07-Aug-2020 14:27:01

   MATLAB 9.5.0.944444 (R2018b)

   Copyright (c) 1993-2002 dSPACE GmbH, GERMANY

 *****************************************************************************/

/* ===== List of model tasks and assigned interrupt sources ================

   Timer Task 1 [1e-06 0] s       : DIO CL1 PWM Port 3 Channel 1 Falling edge

  * ========================================================================= */

#ifndef  _RTI_TH_MODEL_C__
# define _RTI_TH_MODEL_C__

/* ===== File includes ===================================================== */

/* Auxiliary functions of TaskHandling*/

/* No sub-interrupts used by application: */
/* RTITH_USES_SUBINT not defined for rti_th_aux.c */
# include <rti_th_aux.c>

/* rtkernel.h already included in RTI Simulation Engine. */

/* ===== Macro definitions ================================================= */

/* Number of local tasks of the specific type */
# define  RTITH_TIMER_TASKS_LOCAL_NUM_OF      (1)
# define  RTITH_HWINT_TASKS_LOCAL_NUM_OF      (0)
# define  RTITH_SWINT_TASKS_LOCAL_NUM_OF      (0)
# define  RTITH_TMRINT_TASKS_LOCAL_NUM_OF     (0)

# define  RTITH_INT_TASKS_ALL_LOCAL_NUM_OF    (0)
# define  RTITH_TASKS_ALL_LOCAL_NUM_OF        (1)

/* Default scaling factor for timer tasks */
# ifndef  RTI_TIMER_TASK_TIME_SCALE
#   define RTI_TIMER_TASK_TIME_SCALE           (1.0)
# endif

/* Avoid compilation with invalid timer task mode */
# ifdef MULTITASKING
#   error Cannot compile in multiple timer tasks mode (.\Control_APF7_nuevo_MicroLabBox_rti1202\Control_APF7_nuevo_MicroLabBox_th.c is for ST).
# endif


/* ===== Type definitions ================================================ */

typedef struct tagRtiTimerTask1TriggerSource {
  int service;
  int subentry;
  int subsubentry;
} RtiTimerTask1TriggerSource;


/* ===== Global declarations =============================================== */

/* Pointers to task information variables */
  /* --- Task  1 : Timer Task 1 (TIMER 120XDIOCL1PWM_FALLING_EDGEP3Ch1) */
double               *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_STime;
double               *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_TTime;
rtk_task_state_type  *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_TState;
rtk_ovc_check_type   *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_OType;
int                  *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_OMax;
int                  *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_ORpt;
int                  *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_OCnt;
double               *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_TCnt;
int                  *pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_Prio;

/* Pointer to RTK task control block of 'Timer Task 1' */
static rtk_p_task_control_block    pRtiTimerTask1TCB = NULL;


/* ===== Function definitions ============================================== */

/* Interface function of Task Handling to create and bind all tasks */
static void rti_th_initialize(void)
{
  /* --- Local declarations ------------------------------------------------ */

  /* Pointers to task control blocks */
  rtk_p_task_control_block pTask1;  /*  Task (TCB pointer).              */

  int subentry;        /*  RTK subentry.                    */
  int service;         /*  RTK service.                     */

/* Initialize dynamically generated services */

  /* --- Initialization code -----------------------------------------------
   * Task  1 : Timer Task 1 (TIMER 120XDIOCL1PWM_FALLING_EDGEP3Ch1)
   * Priority: 1, Source: 1, Target: 1
   * Source IntNo: DIGITAL_IO_FALLING_EDGE, SubIntNo: RTK_NO_SINT, TaskId: 1
   * ----------------------------------------------------------------------- */
  service   = S_RTLIB_FPGA_IO;                     /*  RTK service.                     */
  subentry = rtk_get_subentry( /* --- Get RTK subentry. ----------- */
      service,                 /*  RTK service.                     */
      IOLIB_SPEC_INT_DIO_CL1_PWM_IO(33),                 /*  Board base address.              */
      DIGITAL_IO_FALLING_EDGE);                /*  Interrupt number.                */
  pTask1   = rtith_create_task( /* --- Create task. ---------------- */
      rti_120XDIOCL1PWM_FALLING_EDGEP3Ch1,                 /*  Task function pointer.           */
      1,                 /*  Task priority.                   */
      ovc_fcn,                 /*  RTK overrun check type.          */
      rti_default_overrun_fcn,                 /*  Overrun handler function.        */
      1,                 /*  Overrun count limit.             */
      1);                /*  Simulink TID.                    */
  rtk_task_name_set( /* --- Set task name. -------------- */
      pTask1,          /*  Task (TCB pointer).              */
      "Timer Task 1");       /*  Task name.                       */
  rtith_bind_interrupt( /* --- Bind interrupt to task. ----- */
      service, subentry,         /*  RTK service, RTK subentry.       */
      pTask1,             /*  Task (TCB pointer).              */
      (1e-06 * RTI_TIMER_TASK_TIME_SCALE),             /*  Sample time or period.           */
      C_LOCAL,             /*  RTK channel.                     */
      -1,             /*  Logical interrupt number.        */
      NULL);            /*  Hook function.                   */
  rtith_set_task_type( /* --- Set RTK task type. ---------- */
      service, subentry,           /*  RTK service, RTK subentry.       */
      RTK_NO_SINT,               /*  Sub-interrupt number.            */
      rtk_tt_periodic,               /*  RTK task type.                   */
      NULL,               /*  Reference task (time stamping).  */
      0,            /*  Sample time offset.              */
      1);           /*  Step multiple.                   */

  /* ... Assign task information variables ................................. */
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_STime = &(pTask1->sample_time);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_TTime = &(pTask1->turnaround_time);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_TState = &(pTask1->state);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_OType = &(pTask1->ovc_type);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_OMax = &(pTask1->ovc_max);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_ORpt = &(pTask1->ovc_repeat);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_OCnt = &(pTask1->ovc_counter);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_TCnt = &(pTask1->tm_task_calls);
  pRti_120XDIOCL1PWM_FALLING_EDGEP3Ch1_Prio = &(pTask1->priority);

  /* ... Assign pointer to RTK task control block of of 'Timer Task 1' ..... */
  pRtiTimerTask1TCB = pTask1;         /*  Reference task (time stamping).  */

  /* ... Mark driving interrupt as unused in non-RT simulation mode ........ */
# ifdef SMODE
#   if SMODE == NRTSIM
  rtith_int_status_bit_clear( /* --------------------------------- */
    service, subentry,                 /*  RTK service, RTK subentry.       */
    RTK_NO_SINT,                     /*  Sub-interrupt number.            */
    RTK_STATUS_USED);       /*  RTK mask: Interrupt is bound.    */
#   endif
# endif

# ifndef FIRST_SIMSTEP_INCREASEMENT
#   define RTI_SE_TMP_OVC_MAXCNT          (12)
#   define RTI_SE_TMP_OVC_NUM_CALLS       (12)

/*  Temporarily disable default overrun handling (for RTI_SE_TMP_OVC_NUM_CALLS task calls) and queue up the TimerTask1TCB on overrun  */
#   if (RTI_SE_INITIAL_OVCREPEAT_BASE_RATE_TASK == 1)
      rtk_setup_temp_overrun_handling(
        pRtiTimerTask1TCB,
        ovc_queue,
        NULL,
        RTI_SE_TMP_OVC_MAXCNT,
        RTI_SE_TMP_OVC_NUM_CALLS
      );
#   endif
# endif

  return;
}

void rti_th_timertask1_trigger_source(RtiTimerTask1TriggerSource* triggerSource)
{
  triggerSource->service = S_RTLIB_FPGA_IO;
  triggerSource->subentry = rtk_get_subentry(
    S_RTLIB_FPGA_IO,
    IOLIB_SPEC_INT_DIO_CL1_PWM_IO(33),
    DIGITAL_IO_FALLING_EDGE);
  triggerSource->subsubentry = RTK_NO_SINT;
}

#endif /* _RTI_TH_MODEL_C__ */

/****** [EOF] ****************************************************************/
