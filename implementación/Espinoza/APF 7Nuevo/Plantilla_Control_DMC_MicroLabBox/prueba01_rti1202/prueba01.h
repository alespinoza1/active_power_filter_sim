

    /*
  * prueba01.h
  *
    * Code generation for model "prueba01".
  *
  * Model version              : 1.5
  * Simulink Coder version : 9.0 (R2018b) 24-May-2018
  * C source code generated on : Tue Apr 16 10:01:03 2019
 * 
 * Target selection: rti1202.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
  */


  #ifndef RTW_HEADER_prueba01_h_
  #define RTW_HEADER_prueba01_h_
  

    

  
#include <string.h>
    #ifndef prueba01_COMMON_INCLUDES_
  # define prueba01_COMMON_INCLUDES_
    #include <brtenv.h>
    #include <rtkernel.h>
    #include <rti_assert.h>
    #include <rtidefineddatatypes.h>
    #include "rtwtypes.h"
      #include "rtw_continuous.h"
      #include "rtw_solver.h"
  #endif /* prueba01_COMMON_INCLUDES_ */
  

    #include "prueba01_types.h"    
        
    /* Shared type includes */
          #include "multiword_types.h"

    


  
  
  
  

  

  

  

  
    /* Macros for accessing real-time model data structure */
    

    #ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm) ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm) (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm) ((rtm)->Timing.taskTime0)
#endif


  
   
    
    
      


  

  

  

  

        
            /* Parameters (default storage) */
          
        struct P_prueba01_T_ {
          

            



        
          
          
		
            
          
            

              
                          
            
                   real_T Constant_Value; /* Expression: 1
  * Referenced by: '<Root>/Constant'
   */
 
            
              
             

          
          
	  
		
                  
      



        };
      

    


      /* Real-time Model Data Structure */
      
  struct tag_RTM_prueba01_T {
            const char_T *errorStatus;

              /*
     * Timing:
           * The following substructure contains information regarding
      * the timing information for the model.
      */
 
  struct  {
            time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    boolean_T stopRequestedFlag;



  } Timing;



  };
      
        
          


  

  

          

      /* Block parameters (default storage) */
      


  extern         P_prueba01_T prueba01_P;



    

  
      /* Model entry point functions */
              extern void prueba01_initialize(void);
            
        
                  extern void prueba01_output(void);
                              extern void prueba01_update(void);
              
    
               extern void prueba01_terminate(void);
             


  

            
          /* Real-time Model object */
          
          


  extern             RT_MODEL_prueba01_T *const prueba01_M;



          


  

  

  

        
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
    * '<Root>' : 'prueba01'
      * '<S1>'   : 'prueba01/DAC_CLASS1_BL1'
      * '<S2>'   : 'prueba01/RTI Data'
      * '<S3>'   : 'prueba01/RTI Data/RTI Data Store'
      * '<S4>'   : 'prueba01/RTI Data/RTI Data Store/RTI Data Store'
      * '<S5>'   : 'prueba01/RTI Data/RTI Data Store/RTI Data Store/RTI Data Store'
   */


  

    #endif /* RTW_HEADER_prueba01_h_ */
