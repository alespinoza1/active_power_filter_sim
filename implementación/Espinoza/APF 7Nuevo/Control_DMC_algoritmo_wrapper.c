
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
			real_T *Icref)
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
    //il_alpha =  sqrt(2/3)*(ial_med-ibl_med/2-icl_med/2);
    il_alpha =  ial_med;
    il_beta = sqrt(2)*(ibl_med/2-icl_med/2);

    vs_alpha =  sqrt(2/3)*(vas_med-vbs_med/2-vcs_med/2);
    vs_beta = sqrt(2)*(vbs_med/2-vcs_med/2);

    PL = vs_alpha*il_alpha + vs_beta*il_beta;
    QL = vs_beta*il_alpha - vs_alpha*il_beta;
    
    Pc = PL;
    Qc = 0;

    D = vs_alpha*vs_alpha + vs_beta*vs_beta + 1e-6;

    ic_alpha = (vs_alpha*Pc + vs_beta*Qc)/D;
    ic_beta = (vs_beta*Pc - vs_alpha*Qc)/D;

    ica_ref=  sqrt(2/3)*ic_alpha;
    icb_ref=  sqrt(2/3)*(-ic_alpha/2 + sqrt(3)/2*ic_beta);
    icc_ref=  sqrt(2/3)*(-ic_alpha/2 - sqrt(3)/2*ic_beta);
    

     //valores iniciales óptimos
    fc_Joa = 1e8; 
    fc_Job = 1e8; 
    fc_Joc = 1e8; 
    ioa = 0; 
    iob = 0; 
    ioc = 0;
    
  //Se recorre la matriz de disparos  
    for (ind=0;ind<c;ind++){
    
       ica_km1=(1-Ts*Rc/Lc)*iac_med + Ts/Lc*(vas_med-Vc[ind]*Vdc);
       icb_km1=(1-Ts*Rc/Lc)*ibc_med + Ts/Lc*(vbs_med-Vc[ind]*Vdc);
       icc_km1=(1-Ts*Rc/Lc)*icc_med + Ts/Lc*(vcs_med-Vc[ind]*Vdc);
       
       
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
       fc[0] = fc_Jb;
       fc[0] = fc_Jc;
    
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


