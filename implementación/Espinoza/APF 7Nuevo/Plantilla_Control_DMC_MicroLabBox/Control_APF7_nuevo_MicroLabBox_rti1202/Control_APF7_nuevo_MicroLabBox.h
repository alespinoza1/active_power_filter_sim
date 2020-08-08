/*
 * Control_APF7_nuevo_MicroLabBox.h
 *
 * Code generation for model "Control_APF7_nuevo_MicroLabBox".
 *
 * Model version              : 1.323
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Fri Aug  7 14:27:03 2020
 *
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Control_APF7_nuevo_MicroLabBox_h_
#define RTW_HEADER_Control_APF7_nuevo_MicroLabBox_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef Control_APF7_nuevo_MicroLabBox_COMMON_INCLUDES_
# define Control_APF7_nuevo_MicroLabBox_COMMON_INCLUDES_
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Control_APF7_nuevo_MicroLabBox_COMMON_INCLUDES_ */

#include "Control_APF7_nuevo_MicroLabBox_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

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

#define Control_APF7_nuevo_MicroLabBox_M (Control_APF7_nuevo_MicroLabB_M)

/* Block signals (default storage) */
typedef struct {
  real_T Gain;                         /* '<S9>/Gain' */
  real_T Sum;                          /* '<S9>/Sum' */
  real_T SFunction1;                   /* '<S24>/S-Function1' */
  real_T SFunction1_h;                 /* '<S25>/S-Function1' */
  real_T SFunction1_c;                 /* '<S26>/S-Function1' */
  real_T SFunction1_n;                 /* '<S18>/S-Function1' */
  real_T SFunction1_o;                 /* '<S19>/S-Function1' */
  real_T SFunction1_f;                 /* '<S20>/S-Function1' */
  real_T SFunction1_j;                 /* '<S21>/S-Function1' */
  real_T SFunction1_l;                 /* '<S22>/S-Function1' */
  real_T SFunction1_ng;                /* '<S23>/S-Function1' */
  real_T SFunction1_b;                 /* '<S27>/S-Function1' */
  real_T SFunction1_i;                 /* '<S28>/S-Function1' */
  real_T SFunction1_jc;                /* '<S29>/S-Function1' */
  real_T TmpSignalConversionAtControlado[26];
  real_T contador[6];                  /* '<S1>/Controlador' */
  real_T Controlador_o2[3];            /* '<S1>/Controlador' */
  real_T Controlador_o3[6];            /* '<S1>/Controlador' */
  real_T Controlador_o4[3];            /* '<S1>/Controlador' */
  real_T Controlador_o5[2];            /* '<S1>/Controlador' */
  real_T Controlador_o6[2];            /* '<S1>/Controlador' */
  real_T Controlador_o7[2];            /* '<S1>/Controlador' */
  real_T Controlador_o8[3];            /* '<S1>/Controlador' */
  real_T Controlador_o9[3];            /* '<S1>/Controlador' */
  real_T Controlador_o10[12];          /* '<S1>/Controlador' */
  real_T PLQL[2];                      /* '<S5>/S-Function Builder1' */
  real_T Qc_Qs[2];                     /* '<S6>/S-Function Builder1' */
  real_T Output;                       /* '<S45>/Output' */
  real_T Gain1;                        /* '<S36>/Gain1' */
  real_T Gain1_j;                      /* '<S37>/Gain1' */
  real_T Gain1_m;                      /* '<S38>/Gain1' */
  real_T TmpSignalConversionAtSFunctionB[6];
  real_T Vec_SWA[6];                   /* '<S46>/S-Function Builder1' */
  real_T Gain1_h;                      /* '<S39>/Gain1' */
  real_T Gain1_n;                      /* '<S40>/Gain1' */
  real_T Gain1_d;                      /* '<S41>/Gain1' */
  real_T TmpSignalConversionAtSFunctio_i[6];
  real_T Vec_SWB[6];                   /* '<S47>/S-Function Builder1' */
  real_T Gain1_f;                      /* '<S42>/Gain1' */
  real_T Gain1_c;                      /* '<S43>/Gain1' */
  real_T Gain1_dv;                     /* '<S44>/Gain1' */
  real_T TmpSignalConversionAtSFuncti_ig[6];
  real_T Vec_SWC[6];                   /* '<S48>/S-Function Builder1' */
  real_T varfiltrada[12];              /* '<S11>/S-Function Builder1' */
  real_T fc[3];                        /* '<S12>/S-Function Builder1' */
  real_T ickm1[3];                     /* '<S13>/S-Function Builder1' */
  real_T icref[3];                     /* '<S14>/S-Function Builder1' */
  real_T ploss[3];                     /* '<S15>/S-Function Builder1' */
  real_T vsalfabeta[2];                /* '<S16>/S-Function Builder1' */
  real_T Vs_med[3];
  real_T Vs_med_j[3];                  /* '<S4>/S-Function Builder1' */
  real_T TmpSignalConversionAtSFunctio_f[3];
  real_T IL_med[3];                    /* '<S4>/S-Function Builder' */
  real_T TmpSignalConversionAtSFunctio_h[3];
  real_T Ic_med[3];                    /* '<S4>/S-Function Builder2' */
  real_T TmpSignalConversionAtSFuncti_iv[3];
  real_T Vdclink[3];                   /* '<S4>/S-Function Builder3' */
  boolean_T NOT4;                      /* '<S33>/NOT4' */
  boolean_T NOT5;                      /* '<S33>/NOT5' */
  boolean_T NOT;                       /* '<S33>/NOT' */
  boolean_T NOT3;                      /* '<S33>/NOT3' */
  boolean_T NOT2;                      /* '<S33>/NOT2' */
  boolean_T NOT1;                      /* '<S33>/NOT1' */
  boolean_T NOT_h;                     /* '<S34>/NOT' */
  boolean_T NOT4_e;                    /* '<S34>/NOT4' */
  boolean_T NOT5_a;                    /* '<S34>/NOT5' */
  boolean_T NOT3_k;                    /* '<S34>/NOT3' */
  boolean_T NOT2_i;                    /* '<S34>/NOT2' */
  boolean_T NOT1_m;                    /* '<S34>/NOT1' */
  boolean_T NOT_b;                     /* '<S35>/NOT' */
  boolean_T NOT4_h;                    /* '<S35>/NOT4' */
  boolean_T NOT5_p;                    /* '<S35>/NOT5' */
  boolean_T NOT3_f;                    /* '<S35>/NOT3' */
  boolean_T NOT2_b;                    /* '<S35>/NOT2' */
  boolean_T NOT1_b;                    /* '<S35>/NOT1' */
} B_Control_APF7_nuevo_MicroLab_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<S9>/Memory' */
  real_T Memory1_PreviousInput;        /* '<S9>/Memory1' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay_RWORK;              /* '<S8>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay1_RWORK;             /* '<S8>/Transport Delay1' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S8>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay1_PWORK;             /* '<S8>/Transport Delay1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S8>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay1_IWORK;             /* '<S8>/Transport Delay1' */
} DW_Control_APF7_nuevo_MicroLa_T;

/* Parameters (default storage) */
struct P_Control_APF7_nuevo_MicroLab_T_ {
  real_T Ganancia_Ica;                 /* Variable: Ganancia_Ica
                                        * Referenced by: '<S4>/Gain6'
                                        */
  real_T Ganancia_Icb;                 /* Variable: Ganancia_Icb
                                        * Referenced by: '<S4>/Gain7'
                                        */
  real_T Ganancia_Icc;                 /* Variable: Ganancia_Icc
                                        * Referenced by: '<S4>/Gain8'
                                        */
  real_T Ganancia_Ila;                 /* Variable: Ganancia_Ila
                                        * Referenced by: '<S4>/Gain3'
                                        */
  real_T Ganancia_Ilb;                 /* Variable: Ganancia_Ilb
                                        * Referenced by: '<S4>/Gain4'
                                        */
  real_T Ganancia_Ilc;                 /* Variable: Ganancia_Ilc
                                        * Referenced by: '<S4>/Gain5'
                                        */
  real_T Ganancia_Vsa;                 /* Variable: Ganancia_Vsa
                                        * Referenced by: '<S4>/Gain'
                                        */
  real_T Ganancia_Vsb;                 /* Variable: Ganancia_Vsb
                                        * Referenced by: '<S4>/Gain10'
                                        */
  real_T Ganancia_Vsc;                 /* Variable: Ganancia_Vsc
                                        * Referenced by: '<S4>/Gain11'
                                        */
  real_T Ica_offset;                   /* Variable: Ica_offset
                                        * Referenced by: '<S4>/Constant6'
                                        */
  real_T Icb_offset;                   /* Variable: Icb_offset
                                        * Referenced by: '<S4>/Constant7'
                                        */
  real_T Icc_offset;                   /* Variable: Icc_offset
                                        * Referenced by: '<S4>/Constant8'
                                        */
  real_T Ila_offset;                   /* Variable: Ila_offset
                                        * Referenced by: '<S4>/Constant3'
                                        */
  real_T Ilb_offset;                   /* Variable: Ilb_offset
                                        * Referenced by: '<S4>/Constant4'
                                        */
  real_T Ilc_offset;                   /* Variable: Ilc_offset
                                        * Referenced by: '<S4>/Constant5'
                                        */
  real_T Lc;                           /* Variable: Lc
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T Rc;                           /* Variable: Rc
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Ts;                           /* Variable: Ts
                                        * Referenced by:
                                        *   '<Root>/Period'
                                        *   '<S1>/Constant'
                                        *   '<S8>/Transport Delay'
                                        *   '<S8>/Transport Delay1'
                                        */
  real_T Vdc;                          /* Variable: Vdc
                                        * Referenced by: '<S1>/Constant3'
                                        */
  real_T Vsa_offset;                   /* Variable: Vsa_offset
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Vsb_offset;                   /* Variable: Vsb_offset
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Vsc_offset;                   /* Variable: Vsc_offset
                                        * Referenced by: '<S4>/Constant2'
                                        */
  real_T e;                            /* Variable: e
                                        * Referenced by: '<S1>/Constant8'
                                        */
  real_T f;                            /* Variable: f
                                        * Referenced by: '<S1>/Constant10'
                                        */
  real_T g;                            /* Variable: g
                                        * Referenced by: '<S1>/Constant9'
                                        */
  real_T ki;                           /* Variable: ki
                                        * Referenced by: '<S1>/Constant5'
                                        */
  real_T kp;                           /* Variable: kp
                                        * Referenced by: '<S1>/Constant4'
                                        */
  real_T lamda;                        /* Variable: lamda
                                        * Referenced by: '<S1>/Constant6'
                                        */
  real_T sat;                          /* Variable: sat
                                        * Referenced by: '<S1>/Constant13'
                                        */
  real_T x;                            /* Variable: x
                                        * Referenced by: '<S1>/Constant11'
                                        */
  real_T y;                            /* Variable: y
                                        * Referenced by: '<S1>/Constant12'
                                        */
  real_T z;                            /* Variable: z
                                        * Referenced by: '<S1>/Constant7'
                                        */
  real_T RepeatingSequence1_rep_seq_y[3];/* Mask Parameter: RepeatingSequence1_rep_seq_y
                                          * Referenced by: '<S45>/Look-Up Table1'
                                          */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S9>/Constant1'
                                        */
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T Memory_InitialCondition;      /* Expression: -1
                                        * Referenced by: '<S9>/Memory'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 20
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: 1
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Memory1_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S9>/Memory1'
                                        */
  real_T Gain9_Gain;                   /* Expression: 10.0
                                        * Referenced by: '<S4>/Gain9'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: 10.0
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: 10.0
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real_T Gain15_Gain;                  /* Expression: 474.63
                                        * Referenced by: '<S4>/Gain15'
                                        */
  real_T Gain17_Gain;                  /* Expression: 474.63
                                        * Referenced by: '<S4>/Gain17'
                                        */
  real_T Gain18_Gain;                  /* Expression: 474.63
                                        * Referenced by: '<S4>/Gain18'
                                        */
  real_T Constant_Value_g;             /* Expression: period
                                        * Referenced by: '<S45>/Constant'
                                        */
  real_T LookUpTable1_bp01Data[3];     /* Expression: rep_seq_t - min(rep_seq_t)
                                        * Referenced by: '<S45>/Look-Up Table1'
                                        */
  real_T Gain1_Gain_f;                 /* Expression: -1
                                        * Referenced by: '<S36>/Gain1'
                                        */
  real_T TransportDelay_InitOutput;    /* Expression: 0
                                        * Referenced by: '<S8>/Transport Delay'
                                        */
  real_T Gain1_Gain_c;                 /* Expression: -1
                                        * Referenced by: '<S37>/Gain1'
                                        */
  real_T TransportDelay1_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S8>/Transport Delay1'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: -1
                                        * Referenced by: '<S38>/Gain1'
                                        */
  real_T Gain1_Gain_fe;                /* Expression: -1
                                        * Referenced by: '<S39>/Gain1'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: -1
                                        * Referenced by: '<S40>/Gain1'
                                        */
  real_T Gain1_Gain_d1;                /* Expression: -1
                                        * Referenced by: '<S41>/Gain1'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: -1
                                        * Referenced by: '<S42>/Gain1'
                                        */
  real_T Gain1_Gain_g;                 /* Expression: -1
                                        * Referenced by: '<S43>/Gain1'
                                        */
  real_T Gain1_Gain_cv;                /* Expression: -1
                                        * Referenced by: '<S44>/Gain1'
                                        */
  real_T DutyCycle_Value;              /* Expression: 0.5
                                        * Referenced by: '<Root>/Duty Cycle'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Control_APF7_nuevo_Mi_T {
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
extern P_Control_APF7_nuevo_MicroLab_T Control_APF7_nuevo_MicroLabBo_P;

/* Block signals (default storage) */
extern B_Control_APF7_nuevo_MicroLab_T Control_APF7_nuevo_MicroLabBo_B;

/* Block states (default storage) */
extern DW_Control_APF7_nuevo_MicroLa_T Control_APF7_nuevo_MicroLabB_DW;

/* Model entry point functions */
extern void Control_APF7_nuevo_MicroLabBox_initialize(void);
extern void Control_APF7_nuevo_MicroLabBox_output(void);
extern void Control_APF7_nuevo_MicroLabBox_update(void);
extern void Control_APF7_nuevo_MicroLabBox_terminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Control_APF7_nuevo_MicroLabBox_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_Control_APF7_nuevo_M_T *const Control_APF7_nuevo_MicroLabB_M;

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
 * '<Root>' : 'Control_APF7_nuevo_MicroLabBox'
 * '<S1>'   : 'Control_APF7_nuevo_MicroLabBox/Controlador'
 * '<S2>'   : 'Control_APF7_nuevo_MicroLabBox/DIO_CLASS1_HWINT_BL2'
 * '<S3>'   : 'Control_APF7_nuevo_MicroLabBox/DIO_CLASS1_PWM_BL1'
 * '<S4>'   : 'Control_APF7_nuevo_MicroLabBox/Mediciones1'
 * '<S5>'   : 'Control_APF7_nuevo_MicroLabBox/Pl QL '
 * '<S6>'   : 'Control_APF7_nuevo_MicroLabBox/QcQsfiltrada'
 * '<S7>'   : 'Control_APF7_nuevo_MicroLabBox/RTI Data'
 * '<S8>'   : 'Control_APF7_nuevo_MicroLabBox/Subsystem3'
 * '<S9>'   : 'Control_APF7_nuevo_MicroLabBox/TicTac'
 * '<S10>'  : 'Control_APF7_nuevo_MicroLabBox/Timer Task Assignment1'
 * '<S11>'  : 'Control_APF7_nuevo_MicroLabBox/filtros'
 * '<S12>'  : 'Control_APF7_nuevo_MicroLabBox/funcionCosto '
 * '<S13>'  : 'Control_APF7_nuevo_MicroLabBox/ic km1 '
 * '<S14>'  : 'Control_APF7_nuevo_MicroLabBox/ic ref '
 * '<S15>'  : 'Control_APF7_nuevo_MicroLabBox/ploss'
 * '<S16>'  : 'Control_APF7_nuevo_MicroLabBox/vs alfa beta '
 * '<S17>'  : 'Control_APF7_nuevo_MicroLabBox/DIO_CLASS1_HWINT_BL2/Common Hardware Interrupt Interface'
 * '<S18>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/ILa'
 * '<S19>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/ILb '
 * '<S20>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/ILc'
 * '<S21>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/Ica'
 * '<S22>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/Icb'
 * '<S23>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/Icc'
 * '<S24>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/Vsa'
 * '<S25>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/Vsb'
 * '<S26>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/Vsc'
 * '<S27>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/dclink1'
 * '<S28>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/dclink2'
 * '<S29>'  : 'Control_APF7_nuevo_MicroLabBox/Mediciones1/dclink3'
 * '<S30>'  : 'Control_APF7_nuevo_MicroLabBox/RTI Data/RTI Data Store'
 * '<S31>'  : 'Control_APF7_nuevo_MicroLabBox/RTI Data/RTI Data Store/RTI Data Store'
 * '<S32>'  : 'Control_APF7_nuevo_MicroLabBox/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
 * '<S33>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Inversion   '
 * '<S34>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Inversion2'
 * '<S35>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Inversion3'
 * '<S36>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block a1'
 * '<S37>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block a2'
 * '<S38>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block a3'
 * '<S39>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block b1'
 * '<S40>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block b2'
 * '<S41>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block b3'
 * '<S42>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block c1'
 * '<S43>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block c2'
 * '<S44>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Modulation block c3'
 * '<S45>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Repeating Sequence1'
 * '<S46>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Subsystem'
 * '<S47>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Subsystem1'
 * '<S48>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/Subsystem2'
 * '<S49>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA'
 * '<S50>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB'
 * '<S51>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC'
 * '<S52>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF'
 * '<S53>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF1'
 * '<S54>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF10'
 * '<S55>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF7'
 * '<S56>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF8'
 * '<S57>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseA/Señales de Conmutación  APF9'
 * '<S58>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF10'
 * '<S59>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF2'
 * '<S60>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF3'
 * '<S61>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF7'
 * '<S62>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF8'
 * '<S63>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseB/Señales de Conmutación  APF9'
 * '<S64>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF10'
 * '<S65>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF4'
 * '<S66>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF6'
 * '<S67>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF7'
 * '<S68>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF8'
 * '<S69>'  : 'Control_APF7_nuevo_MicroLabBox/Subsystem3/faseC/Señales de Conmutación  APF9'
 * '<S70>'  : 'Control_APF7_nuevo_MicroLabBox/Timer Task Assignment1/SubSystem'
 */
#endif                                 /* RTW_HEADER_Control_APF7_nuevo_MicroLabBox_h_ */
