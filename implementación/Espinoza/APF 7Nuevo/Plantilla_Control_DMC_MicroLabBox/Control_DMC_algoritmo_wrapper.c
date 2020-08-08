
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <parametros.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 14
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void Control_DMC_algoritmo_Outputs_wrapper(const real_T *in,
			real_T *Sw,
			real_T *io,
			real_T *fc,
			real_T *Vs_alfabeta,
			real_T *IL_alfabeta,
			real_T *PLQL,
			real_T *Icref,
			real_T *ic_km1,
			real_T *bandera)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/*%%% Lectura de variables */

Ts = in[0];
vas_med=in[1];
vbs_med=in[2];
vcs_med=in[3];

ial_med=in[4];
ibl_med=in[5];
icl_med=in[6];

iac_med =in[7];
ibc_med =in[8];
icc_med =in[9];

Rc = in[10];
Lc = in[11];
Vdc = in[12];
vect = in[13];

//Se espera el tiempo de muestreo

//Se crea la referencia
    //il_alpha =  sqrt(0.66667)*(ial_med-ibl_med*0.5-icl_med*0.5);
    //il_beta = sqrt(2)*(ibl_med*0.5-icl_med*0.5)
    
    il_alpha =  0.81649658*(ial_med*0.990268051  - ibl_med*0.374606579 - icl_med*0.615661475);
    il_beta = 0.81649658*(-ial_med*0.1391731053 + ibl_med*0.927183854 - icl_med*0.788077604);
    
    //transformada alfa beta de Ic
    ic_aux_alpha =  0.81649658*(iac_med*0.990268051  - ibc_med*0.374606579 - icc_med*0.615661475);
    ic_aux_beta = 0.81649658*(-iac_med*0.1391731053 + ibc_med*0.927183854 - icc_med*0.788077604);

    vs_alpha =  sqrt(0.66667)*(vas_med-vbs_med*0.5-vcs_med*0.5);
    vs_beta = sqrt(2)*(vbs_med*0.5-vcs_med*0.5);

    PL = vs_alpha*il_alpha + vs_beta*il_beta;
    QL = vs_beta*il_alpha - vs_alpha*il_beta;
    
    Pc = 0;
    Qc = -QL;
   // Qc = 0;

    D = vs_alpha*vs_alpha + vs_beta*vs_beta + 1e-6;

    ic_alpha = (vs_alpha*Pc + vs_beta*Qc)/D;
    ic_beta = (vs_beta*Pc - vs_alpha*Qc)/D;

   
    
     ica_ref=  sqrt(0.66667)*ic_alpha;
     icb_ref=  sqrt(0.66667)*(-ic_alpha*0.5 + sqrt(3)*0.5*ic_beta);
     icc_ref=  sqrt(0.66667)*(-ic_alpha*0.5 - sqrt(3)*0.5*ic_beta);
    
     //Ica calibrado
     ica_med_cal=  sqrt(0.66667)*ic_aux_alpha;
     icb_med_cal=  sqrt(0.66667)*(-ic_aux_alpha*0.5 + sqrt(3)*0.5*ic_aux_beta);
     icc_med_cal=  sqrt(0.66667)*(-ic_aux_alpha*0.5 - sqrt(3)*0.5*ic_aux_beta);
       
            
     
//       ica_km1_1=(1-Ts*Rc/Lc)*ica_med_cal + Ts/Lc*(vas_med-Vc[ioa]*Vdc);
//       icb_km1_1=(1-Ts*Rc/Lc)*icb_med_cal + Ts/Lc*(vbs_med-Vc[iob]*Vdc);
//       icc_km1_1=(1-Ts*Rc/Lc)*icc_med_cal + Ts/Lc*(vcs_med-Vc[ioc]*Vdc);
 
     //valores iniciales óptimos
    fc_Joa = 1e8; 
    fc_Job = 1e8; 
    fc_Joc = 1e8; 
    
    ioa = 0; 
    iob = 0;  
    ioc = 0; 
    

    
  //Se recorre la matriz de disparos  
   for(ind=0;ind<4;ind++){
     //Original
//        ica_km1=(1-Ts*Rc/Lc)*iac_med + Ts/Lc*(vas_med-Vc[ind]*Vdc);
//        icb_km1=(1-Ts*Rc/Lc)*ibc_med + Ts/Lc*(vbs_med-Vc[ind]*Vdc);
//        icc_km1=(1-Ts*Rc/Lc)*icc_med + Ts/Lc*(vcs_med-Vc[ind]*Vdc);
       
       
       //Con calibracion de Ic
       ica_km1=(1-Ts*Rc/Lc)*ica_med_cal + Ts/Lc*(vas_med-Vc[ind]*Vdc);
       icb_km1=(1-Ts*Rc/Lc)*icb_med_cal + Ts/Lc*(vbs_med-Vc[ind]*Vdc);
       icc_km1=(1-Ts*Rc/Lc)*icc_med_cal + Ts/Lc*(vcs_med-Vc[ind]*Vdc);
       
       
   //para k+2    
//        ica_km1=(1-Ts*Rc/Lc)*ica_km1_1 + Ts/Lc*(vas_med-Vc[ind]*Vdc);
//        icb_km1=(1-Ts*Rc/Lc)*icb_km1_1 + Ts/Lc*(vbs_med-Vc[ind]*Vdc);
//        icc_km1=(1-Ts*Rc/Lc)*icc_km1_1 + Ts/Lc*(vcs_med-Vc[ind]*Vdc);
       
            
       //Se calcula el error de seguimento de corriente 
	   dif_a = ica_ref - ica_km1;
	   dif_b = icb_ref - icb_km1;
       dif_c = icc_ref - icc_km1;
       //Se calcula el valor de la función de coste
       fc_Ja = dif_a*dif_a;
       fc_Jb = dif_b*dif_b;
       fc_Jc = dif_c*dif_c;
       
     
       
            
       //Se evalua la función de coste
        if (fc_Ja < fc_Joa){
            fc_Joa = fc_Ja;
            ioa = ind;
            //ioa = vect;
            //io[0] = ioa;
        }
        
        if (fc_Jb < fc_Job){
            fc_Job = fc_Jb;
            iob = ind;
            //iob = vect;
            //io[1] = iob;
        }   
        
        if (fc_Jc < fc_Joc){
            fc_Joc = fc_Jc;
            ioc = ind; 
            //ioc = vect;
            //io[2] = ioc;
        }
    
       
    }
    
    // Indice de vectores optimos       
       io[0] = ioa;
       io[1] = iob;
       io[2] = ioc;
    // funcion de costo   
       fc[0] = fc_Ja;
       fc[1] = fc_Jb;
       fc[2] = fc_Jc;
    
    //Visualizacion de parametros
       Vs_alfabeta[0] = vs_alpha;
       Vs_alfabeta[1] = vs_beta;
       
       IL_alfabeta[0] = il_alpha;
       IL_alfabeta[1] = il_beta;
       
       PLQL[0] = PL;
       PLQL[1] = QL;
       
       Icref[0] = ica_ref;
       Icref[1] = icb_ref;
       Icref[2] = icc_ref;
       
       ic_km1[0] = ica_km1;
       ic_km1[1] = icb_km1;
       ic_km1[2] = icc_km1;
 
  
         
 switch (ioa)
{
    case 0:
        Sw[0]=0;
        Sw[1]=0;
        break;
    case 1:
        Sw[0]=0;
        Sw[1]=1;
        break;
    case 2:
        Sw[0]=1;
        Sw[1]=0;
        break;
    case 3:
        Sw[0]=1;
        Sw[1]=1;
        break;
        
 }
 
 switch (iob)
{
    case 0:
        Sw[2]=0;
        Sw[3]=0;
        break;
    case 1:
        Sw[2]=0;
        Sw[3]=1;
        break;
    case 2:
        Sw[2]=1;
        Sw[3]=0;
        break;
    case 3:
        Sw[2]=1;
        Sw[3]=1;
        break;
        
 }
 
 switch (ioc)
{
    case 0:
        Sw[4]=0;
        Sw[5]=0;
        break;
    case 1:
        Sw[4]=0;
        Sw[5]=1;
        break;
    case 2:
        Sw[4]=1;
        Sw[5]=0;
        break;
    case 3:
        Sw[4]=1;
        Sw[5]=1;
        break;
        
 }
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


