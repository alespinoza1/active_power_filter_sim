

    
  
    /*
    * prueba01.c
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



    

  #include "prueba01_trc_ptr.h"
        #include "prueba01.h"

        #include "prueba01_private.h"



  

  

  

  

  

  

  

  

  

  

    
    

  

  
      
    
    
    
    
    
    

  
        /* Real-time model */
          


  RT_MODEL_prueba01_T prueba01_M_;

        


  RT_MODEL_prueba01_T *const prueba01_M = &prueba01_M_;



  

  

  

  

    
  
  
    
  
  
        
        
          
    /* Model output function */
    
              void prueba01_output(void) 
    {
      
    
    
        
      
      

      

        
  

     
        
  

                                  

    
 
    

    
 
/* S-Function (rti_commonblock): '<S1>/S-Function1' incorporates:
 *  Constant: '<Root>/Constant'
 */
                /* This comment workarounds a code generation problem */
      
      
  /* --- prueba01/DAC_CLASS1_BL1 --- */
  /* --- [RTI120X, DAC C1] - Channel: 12 --- */
  {
    /* define variables required for DAC realtime functions */
    Float64 inportDacData=0.0;




      inportDacData = (real_T) prueba01_P.Constant_Value;

      /* write value of CL1 DAC for output channel 12 */
      DacCl1AnalogOut_setOutputValue(pRTIDacC1AnalogOut_Ch_12, DAC_CLASS1_CHANNEL_12, inportDacData);

    DacCl1AnalogOut_write(pRTIDacC1AnalogOut_Ch_12);
  }

 
   
  
    
    
 






        
  

    

    
    


      
          
  

    }
      

        
    
    /* Model update function */
    
              void prueba01_update(void) 
    {
      
    
    
    
    
        
    
    
      
  

      
  

                      
  

      
  
  
    
    

            /* Update absolute time for base rate */
            /* The "clockTick0" counts the number of times the code of this task has 
    * been executed. The absolute time is the multiplication of "clockTick0" 
    * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not 
    * overflow during the application lifespan selected.
      * Timer of this task consists of two 32 bit unsigned integers. 
      * The two integers represent the low bits Timing.clockTick0 and the high bits 
      * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment. 
    */

    if(!(++prueba01_M->Timing.clockTick0)) {
 ++prueba01_M->Timing.clockTickH0; 
} prueba01_M->Timing.taskTime0 = prueba01_M->Timing.clockTick0 * prueba01_M->Timing.stepSize0 + prueba01_M->Timing.clockTickH0 * prueba01_M->Timing.stepSize0 * 4294967296.0;


        

    


    
    
  
  

    

    
    
    

      
      
    }
      




  







  /* Model initialize function */
  
      void prueba01_initialize(void)
  { 
      


    
    
    
    
        
    
    
        /* Registration code */
            
      
      
  


      
            
            
            /* initialize real-time model */
            (void) memset((void *)prueba01_M, 0,
sizeof(RT_MODEL_prueba01_T));
            
            
            
  
  
  

  
  
  
      
        
        
          
                prueba01_M->Timing.stepSize0  = 1.0E-6;
        
        
            
  

        
      
      
      
  
  

  
  
  


  







    


  

          

  
        {
      
    /* user code (registration function declaration) */
        /*Initialize global TRC pointers. */
    prueba01_rti_init_trc_pointers();

  }

      

    
    
    
        






      
    
    
        

  


      
  


  }    




      
  


  
    
    /* Model terminate function */
          void prueba01_terminate(void)

    {
      

      
                                
  



          
  



                    
                      /* Terminate for S-Function (rti_commonblock): '<S1>/S-Function1' incorporates:
 *  Constant: '<Root>/Constant'
 */
          
            
      
    /* --- prueba01/DAC_CLASS1_BL1 --- */
    /* --- [RTI120X, DAC C1] - Channel: 12 --- */

      /* All channel outputs are set to high impedance state */
      DacCl1AnalogOut_setOutputHighZ(pRTIDacC1AnalogOut_Ch_12, DAC_CLASS1_HIGH_Z_ON);

    /* Deactivates AnalogOut functionality */
    DacCl1AnalogOut_stop(pRTIDacC1AnalogOut_Ch_12);



 




    

            
  



    




      
          
  

    }
      
  




  
  
   



  

  

  

  
