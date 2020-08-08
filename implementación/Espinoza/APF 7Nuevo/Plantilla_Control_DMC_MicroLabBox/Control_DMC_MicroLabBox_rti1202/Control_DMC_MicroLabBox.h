/*
 * Control_DMC_MicroLabBox.h
 *
 * Code generation for model "Control_DMC_MicroLabBox".
 *
 * Model version              : 1.144
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Fri Jun  7 14:46:00 2019
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Control_DMC_MicroLabBox_h_
#define RTW_HEADER_Control_DMC_MicroLabBox_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef Control_DMC_MicroLabBox_COMMON_INCLUDES_
# define Control_DMC_MicroLabBox_COMMON_INCLUDES_
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Control_DMC_MicroLabBox_COMMON_INCLUDES_ */

#include "Control_DMC_MicroLabBox_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Gain;                         /* '<S19>/Gain' */
  real_T Sum;                          /* '<S19>/Sum' */
  real_T SFunction1;                   /* '<S28>/S-Function1' */
  real_T SFunction1_h;                 /* '<S29>/S-Function1' */
  real_T SFunction1_c;                 /* '<S30>/S-Function1' */
  real_T SFunction1_n;                 /* '<S22>/S-Function1' */
  real_T SFunction1_o;                 /* '<S23>/S-Function1' */
  real_T SFunction1_f;                 /* '<S24>/S-Function1' */
  real_T SFunction1_j;                 /* '<S25>/S-Function1' */
  real_T SFunction1_l;                 /* '<S26>/S-Function1' */
  real_T SFunction1_ng;                /* '<S27>/S-Function1' */
  real_T TmpSignalConversionAtControlado[14];
  real_T contador[6];                  /* '<S1>/Controlador' */
  real_T Controlador_o2[3];            /* '<S1>/Controlador' */
  real_T Controlador_o3[3];            /* '<S1>/Controlador' */
  real_T Controlador_o4[2];            /* '<S1>/Controlador' */
  real_T Controlador_o5[2];            /* '<S1>/Controlador' */
  real_T Controlador_o6[2];            /* '<S1>/Controlador' */
  real_T Controlador_o7[3];            /* '<S1>/Controlador' */
  real_T Controlador_o8[3];            /* '<S1>/Controlador' */
  real_T Controlador_o9;               /* '<S1>/Controlador' */
  real_T Vec_SW[6];                    /* '<S10>/S-Function Builder1' */
  real_T io[3];                        /* '<S11>/S-Function Builder1' */
  real_T fc[3];                        /* '<S12>/S-Function Builder1' */
  real_T TransportDelay[3];            /* '<S1>/Transport Delay' */
  real_T icref[3];                     /* '<S13>/S-Function Builder1' */
  real_T PLQL[2];                      /* '<S14>/S-Function Builder1' */
  real_T ilalfabeta[2];                /* '<S15>/S-Function Builder1' */
  real_T vsalfabeta[2];                /* '<S16>/S-Function Builder1' */
  real_T ickm1[3];                     /* '<S17>/S-Function Builder1' */
  real_T bandera;                      /* '<S18>/S-Function Builder1' */
  real_T TmpSignalConversionAtSFunctionB[3];
  real_T Vs_med[3];                    /* '<S6>/S-Function Builder1' */
  real_T TmpSignalConversionAtSFunctio_f[3];
  real_T IL_med[3];                    /* '<S6>/S-Function Builder' */
  real_T TmpSignalConversionAtSFunctio_h[3];
  real_T Ic_med[3];                    /* '<S6>/S-Function Builder2' */
  boolean_T NOT;                       /* '<S4>/NOT' */
  boolean_T NOT1;                      /* '<S4>/NOT1' */
  boolean_T NOT2;                      /* '<S4>/NOT2' */
  boolean_T NOT3;                      /* '<S4>/NOT3' */
  boolean_T NOT4;                      /* '<S4>/NOT4' */
  boolean_T NOT5;                      /* '<S4>/NOT5' */
  boolean_T NOT_l;                     /* '<S5>/NOT' */
} B_Control_DMC_MicroLabBox_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<S19>/Memory' */
  real_T Memory1_PreviousInput;        /* '<S19>/Memory1' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[6144];
  } TransportDelay_RWORK;              /* '<S1>/Transport Delay' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *TUbufferPtrs[6];
  } TransportDelay_PWORK;              /* '<S1>/Transport Delay' */

  struct {
    int_T Tail[3];
    int_T Head[3];
    int_T Last[3];
    int_T CircularBufSize[3];
  } TransportDelay_IWORK;              /* '<S1>/Transport Delay' */
} DW_Control_DMC_MicroLabBox_T;

/* Parameters (default storage) */
struct P_Control_DMC_MicroLabBox_T_ {
  real_T Ganancia_Ica;                 /* Variable: Ganancia_Ica
                                        * Referenced by: '<S6>/Gain6'
                                        */
  real_T Ganancia_Icb;                 /* Variable: Ganancia_Icb
                                        * Referenced by: '<S6>/Gain7'
                                        */
  real_T Ganancia_Icc;                 /* Variable: Ganancia_Icc
                                        * Referenced by: '<S6>/Gain8'
                                        */
  real_T Ganancia_Ila;                 /* Variable: Ganancia_Ila
                                        * Referenced by: '<S6>/Gain3'
                                        */
  real_T Ganancia_Ilb;                 /* Variable: Ganancia_Ilb
                                        * Referenced by: '<S6>/Gain4'
                                        */
  real_T Ganancia_Ilc;                 /* Variable: Ganancia_Ilc
                                        * Referenced by: '<S6>/Gain5'
                                        */
  real_T Ganancia_Vsa;                 /* Variable: Ganancia_Vsa
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Ganancia_Vsb;                 /* Variable: Ganancia_Vsb
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real_T Ganancia_Vsc;                 /* Variable: Ganancia_Vsc
                                        * Referenced by: '<S6>/Gain2'
                                        */
  real_T Ica_offset;                   /* Variable: Ica_offset
                                        * Referenced by: '<S6>/Constant6'
                                        */
  real_T Icb_offset;                   /* Variable: Icb_offset
                                        * Referenced by: '<S6>/Constant7'
                                        */
  real_T Icc_offset;                   /* Variable: Icc_offset
                                        * Referenced by: '<S6>/Constant8'
                                        */
  real_T Ila_offset;                   /* Variable: Ila_offset
                                        * Referenced by: '<S6>/Constant3'
                                        */
  real_T Ilb_offset;                   /* Variable: Ilb_offset
                                        * Referenced by: '<S6>/Constant4'
                                        */
  real_T Ilc_offset;                   /* Variable: Ilc_offset
                                        * Referenced by: '<S6>/Constant5'
                                        */
  real_T Lc;                           /* Variable: Lc
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T Rc;                           /* Variable: Rc
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Tm;                           /* Variable: Tm
                                        * Referenced by: '<S1>/Transport Delay'
                                        */
  real_T Ts;                           /* Variable: Ts
                                        * Referenced by:
                                        *   '<Root>/Period'
                                        *   '<S1>/Constant'
                                        */
  real_T Vdc;                          /* Variable: Vdc
                                        * Referenced by: '<S1>/Constant3'
                                        */
  real_T Vsa_offset;                   /* Variable: Vsa_offset
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Vsb_offset;                   /* Variable: Vsb_offset
                                        * Referenced by: '<S6>/Constant1'
                                        */
  real_T Vsc_offset;                   /* Variable: Vsc_offset
                                        * Referenced by: '<S6>/Constant2'
                                        */
  real_T vect;                         /* Variable: vect
                                        * Referenced by: '<S1>/Constant4'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S19>/Constant1'
                                        */
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real_T Memory_InitialCondition;      /* Expression: -1
                                        * Referenced by: '<S19>/Memory'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S19>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 20
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: 1
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Memory1_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S19>/Memory1'
                                        */
  real_T TransportDelay_InitOutput;    /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay'
                                        */
  real_T DutyCycle_Value;              /* Expression: 0.5
                                        * Referenced by: '<Root>/Duty Cycle'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Control_DMC_MicroLabB_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[4];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Control_DMC_MicroLabBox_T Control_DMC_MicroLabBox_P;

/* Block signals (default storage) */
extern B_Control_DMC_MicroLabBox_T Control_DMC_MicroLabBox_B;

/* Block states (default storage) */
extern DW_Control_DMC_MicroLabBox_T Control_DMC_MicroLabBox_DW;

/* Model entry point functions */
extern void Control_DMC_MicroLabBox_initialize(void);
extern void Control_DMC_MicroLabBox_output(void);
extern void Control_DMC_MicroLabBox_update(void);
extern void Control_DMC_MicroLabBox_terminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Control_DMC_MicroLabBox_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_Control_DMC_MicroLab_T *const Control_DMC_MicroLabBox_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Control_DMC_MicroLabBox'
 * '<S1>'   : 'Control_DMC_MicroLabBox/Controlador'
 * '<S2>'   : 'Control_DMC_MicroLabBox/DIO_CLASS1_HWINT_BL2'
 * '<S3>'   : 'Control_DMC_MicroLabBox/DIO_CLASS1_PWM_BL1'
 * '<S4>'   : 'Control_DMC_MicroLabBox/Inversion  de  significancia1'
 * '<S5>'   : 'Control_DMC_MicroLabBox/Inversion  de  significancia2'
 * '<S6>'   : 'Control_DMC_MicroLabBox/Mediciones1'
 * '<S7>'   : 'Control_DMC_MicroLabBox/RTI Data'
 * '<S8>'   : 'Control_DMC_MicroLabBox/Salidas digitales'
 * '<S9>'   : 'Control_DMC_MicroLabBox/Señales de Conmutación  APF5'
 * '<S10>'  : 'Control_DMC_MicroLabBox/Subsystem'
 * '<S11>'  : 'Control_DMC_MicroLabBox/Subsystem1'
 * '<S12>'  : 'Control_DMC_MicroLabBox/Subsystem2'
 * '<S13>'  : 'Control_DMC_MicroLabBox/Subsystem3'
 * '<S14>'  : 'Control_DMC_MicroLabBox/Subsystem4'
 * '<S15>'  : 'Control_DMC_MicroLabBox/Subsystem5'
 * '<S16>'  : 'Control_DMC_MicroLabBox/Subsystem6'
 * '<S17>'  : 'Control_DMC_MicroLabBox/Subsystem7'
 * '<S18>'  : 'Control_DMC_MicroLabBox/Subsystem8'
 * '<S19>'  : 'Control_DMC_MicroLabBox/TicTac'
 * '<S20>'  : 'Control_DMC_MicroLabBox/Timer Task Assignment1'
 * '<S21>'  : 'Control_DMC_MicroLabBox/DIO_CLASS1_HWINT_BL2/Common Hardware Interrupt Interface'
 * '<S22>'  : 'Control_DMC_MicroLabBox/Mediciones1/ILa'
 * '<S23>'  : 'Control_DMC_MicroLabBox/Mediciones1/ILb '
 * '<S24>'  : 'Control_DMC_MicroLabBox/Mediciones1/ILc'
 * '<S25>'  : 'Control_DMC_MicroLabBox/Mediciones1/Ica'
 * '<S26>'  : 'Control_DMC_MicroLabBox/Mediciones1/Icb'
 * '<S27>'  : 'Control_DMC_MicroLabBox/Mediciones1/Icc'
 * '<S28>'  : 'Control_DMC_MicroLabBox/Mediciones1/Vsa'
 * '<S29>'  : 'Control_DMC_MicroLabBox/Mediciones1/Vsb'
 * '<S30>'  : 'Control_DMC_MicroLabBox/Mediciones1/Vsc'
 * '<S31>'  : 'Control_DMC_MicroLabBox/RTI Data/RTI Data Store'
 * '<S32>'  : 'Control_DMC_MicroLabBox/RTI Data/RTI Data Store/RTI Data Store'
 * '<S33>'  : 'Control_DMC_MicroLabBox/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
 * '<S34>'  : 'Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF'
 * '<S35>'  : 'Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF1'
 * '<S36>'  : 'Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF2'
 * '<S37>'  : 'Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF3'
 * '<S38>'  : 'Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF4'
 * '<S39>'  : 'Control_DMC_MicroLabBox/Salidas digitales/Señales de Conmutación  APF5'
 * '<S40>'  : 'Control_DMC_MicroLabBox/Timer Task Assignment1/SubSystem'
 */
#endif                                 /* RTW_HEADER_Control_DMC_MicroLabBox_h_ */
