
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
#include <parametros_nuevo.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 26
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
void Control_APF7_nuevo_algoritmo_Outputs_wrapper(const real_T *in,
			real_T *SwA,
			real_T *io,
			real_T *SwC,
			real_T *fc,
			real_T *Vs_alfabeta,
			real_T *PLQL,
			real_T *QCQS,
			real_T *ic_km1,
			real_T *Icref,
			real_T *Varfiltro)
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
dclink_1 = in[13];
dclink_2 = in[14];
dclink_3 = in[15];
kp = in[16];
ki = in[17];
lamda = in[18];

z = in[19];

e = in[20];
g = in[21];
f = in[22];

x = in[23];
y = in[24];
sat = in[25];
//Se espera el tiempo de muestreo

    //Se implementa el LPF de butterworth de 2do orden con una frecuencia de corte fc
    //Pcbar = (1/e)*(-Pcbarkm2*g - Pcbarkm1*f + Pc*x + Pckm1*y + Pckm2*z);
//     ica_bar = (-ica_barkm2*0.700896781188403 - ica_barkm1*-1.647459981076977 + iac_med*0.013359200027856 + icakm1*0.026718400055713 + icakm2*0.013359200027856);
//     ica_barkm2 = ica_barkm1;
//     ica_barkm1 = ica_bar;
//     icakm2 = icakm1;
//     icakm1 = iac_med;
//     
//     icb_bar = (-icb_barkm2*0.700896781188403 - icb_barkm1*-1.647459981076977 + ibc_med*0.013359200027856 + icbkm1*0.026718400055713 + icbkm2*0.013359200027856);
//     icb_barkm2 = icb_barkm1;
//     icb_barkm1 = icb_bar;
//     icbkm2 = icbkm1;
//     icbkm1 = ibc_med;
//     
//     icc_bar = (-icc_barkm2*0.700896781188403 - icc_barkm1*-1.647459981076977 + icc_med*0.013359200027856 + icckm1*0.026718400055713 + icckm2*0.013359200027856);
//     icc_barkm2 = icc_barkm1;
//     icc_barkm1 = icc_bar;
//     icckm2 = icckm1;
//     icckm1 = icc_med;
    
    

    Vas_N = (1-Ts*3141.592654)*Vas_Nant + (Ts*3141.592654)*Vas_ant;
    Vbs_N = (1-Ts*3141.592654)*Vbs_Nant + (Ts*3141.592654)*Vbs_ant;
    Vcs_N = (1-Ts*3141.592654)*Vcs_Nant + (Ts*3141.592654)*Vcs_ant;

// //Se actualizan las variables
    Vas_Nant = Vas_N;
    Vas_ant = vas_med;
    Vbs_Nant = Vbs_N;
    Vbs_ant = vbs_med;
    Vcs_Nant = Vcs_N;
    Vcs_ant = vcs_med;

//Calculo corriente de linea
    isa = ial_med + iac_med;
    isb = ibl_med + ibc_med;
    isc = icl_med + icc_med;
    
//alfa beta corriente de linea
    is_alpha =  0.81649658*(isa-isb*0.5-isc*0.5);
    is_beta = 0.707106781*(isb-isc);
    
    
//Se crea la referencia
    il_alpha =  0.81649658*(ial_med-ibl_med*0.5-icl_med*0.5);
    il_beta = 0.707106781*(ibl_med-icl_med);
    il0 = 0.57735*(ial_med+ibl_med+icl_med);
    
    
//Alfa beta del voltaje de linea
//     vs_alpha =  0.81649658*(vas_med-vbs_med*0.5-vcs_med*0.5);
//     vs_beta = 0.707106781*(vbs_med-vcs_med);
    vs0 = 0.57735*(vas_med+vbs_med+vcs_med);
    
    vs_alpha =  0.81649658*(Vas_N-Vbs_N*0.5-Vcs_N*0.5);
    vs_beta = 0.707106781*(Vbs_N-Vcs_N);
   // vsp = (vas_med+vbs_med+vcs_med)*0.3333333;
    P_0 = vs0*il0;

//Potencia en la linea
    PS = vs_alpha*is_alpha  + vs_beta*is_beta;
    QS = vs_beta*is_alpha   - vs_alpha*is_beta;
    
    
    //Potencia en la carga
    PL = vs_alpha*il_alpha + vs_beta*il_beta;
    QL = vs_beta*il_alpha - vs_alpha*il_beta;
    
 
    //LPF
    PLN = (1-Ts*125.66)*PLN_ant + (Ts*125.66)*PL_ant;
    QLN = (1-Ts*125.66)*QLN_ant + (Ts*125.66)*QL_ant;
    QSN = (1-Ts*125.66)*QSN_ant + (Ts*125.66)*QS_ant;
//Se actualizan las variables
    PLN_ant = PLN;
    PL_ant = PL;
    QLN_ant = QLN;
    QL_ant = QL;
    QSN_ant = QSN;
    QS_ant = QS;
    
    
    
    
   //Se implementa el LPF de butterworth de 2do orden con una frecuencia de corte fc
    
    Pbar = (1/e)*(-Pbarkm2*g - Pbarkm1*f + PL*x + PLkm1*y + PLkm2*z);
    Pbarkm2 = Pbarkm1;
    Pbarkm1 = Pbar;
    PLkm2 = PLkm1;
    PLkm1 = PL;
    
  //Se implementa el control PI del Dc link asumiendo que se miden solo 3 Vdc

    err1 = Vdc - dclink_1;
       
    up1 = kp*err1*1;
    ui1 = ui1_ant + Ts*ki*err1;
    ui1_ant = ui1;
   //Se satura el termino integral
    if (ui1 < -sat){
        ui1 = -sat;
    }
    if (ui1 > sat){
        ui1 = sat;
    }
    
    upi1 = up1 + ui1;  
    
   
    err2 = Vdc - dclink_2;
    up2 = kp*err2*1;
    ui2 = ui2_ant + Ts*ki*err2;
    ui2_ant = ui2;
    //Se satura el termino integral
    if (ui2 < -sat){
        ui2 = -sat;
    }
    if (ui2 > sat){
        ui2 = sat;
    }
    
    upi2 = up2 + ui2;
    
    
    err3 = Vdc - dclink_3;
    up3 = kp*err3*1;
    ui3 = ui3_ant + Ts*ki*err3;
    ui3_ant = ui3;
    //Se satura el termino integral
    if (ui3 < -sat){
        ui3 = -sat;
    }
    if (ui3 > sat){
        ui3 = sat;
    }
    
    upi3 = up3 + ui3;
    
    upi=(upi1+upi2+upi3)*0.3333333;
    
    //out = vcapbar; 
   
//Se calcula la potencia activa y reactiva que debe generar el DSTATCOM
     Pc1 = -PL + Pbar + upi1;
     Pc2 = -PL + Pbar + upi2;
     Pc3 = -PL + Pbar + upi3;
     Pc = (Pc1 + Pc2 +Pc3)*0.3333333;
     
     
         
     
//Se implementa el LPF de butterworth de 2do orden con una frecuencia de corte fc
    Pcbar = (1/e)*(-Pcbarkm2*g - Pcbarkm1*f + Pc*x + Pckm1*y + Pckm2*z);
    Pcbarkm2 = Pcbarkm1;
    Pcbarkm1 = Pcbar;
    Pckm2 = Pckm1;
    Pckm1 = Pc;
     

   Qc = -QLN;
   D = vs_alpha*vs_alpha + vs_beta*vs_beta + 1e-6;

//Alfa beta de Ic
   
   
   ic_alpha = (vs_alpha*Pcbar + vs_beta*Qc)/D; 
   ic_beta = (vs_beta*Pcbar - vs_alpha*Qc)/D;
    
//     ic_alpha = (vs_alpha*(Pcbar+P_0) + vs_beta*Qc)/D; 
//     ic_beta = (vs_beta*(Pcbar+P_0) - vs_alpha*Qc)/D;
    
// //Generacion de referencia Ic
     ica_ref =  0.81649658*ic_alpha;
     icb_ref =  0.81649658*(-ic_alpha*0.5 + 0.866025403*ic_beta);
     icc_ref =  0.81649658*(-ic_alpha*0.5 - 0.866025403*ic_beta); 
     
//      ica_ref =  0.81649658*(-il0*0.707107 + ic_alpha);
//      icb_ref =  0.81649658*(-ic_alpha*0.5 + 0.866025403*ic_beta);
//      icc_ref =  0.81649658*(-ic_alpha*0.5 - 0.866025403*ic_beta); 
     
//      ica_ref =  0.81649658*(il0*0.707107 + ic_alpha);
//      icb_ref =  0.81649658*(il0*0.707107 -ic_alpha*0.5 + 0.866025403*ic_beta);
//      icc_ref =  0.81649658*(il0*0.707107 -ic_alpha*0.5 - 0.866025403*ic_beta); 
     

//valores iniciales óptimos
// Req = Rc + 70;  
// C1 = Ts*Req/Lc;
// C2 = Ts/Lc;    
// C1 = Ts*Rc/Lc;
// C2 = Ts/Lc;
C3 = Ts*403.2258;
C1 = Ts*35;
C2 = Ts*100;

   
    fc_Joa = 1e8; 
    fc_Job = 1e8; 
    fc_Joc = 1e8; 
    
    ioa = 0; 
    iob = 0;  
    ioc = 0; 
    


  //Se recorre la matriz de disparos  
   for(ind=0;ind<7;ind++){
     //Original
//        ica_km1=(1-C1)*iac_med + C2*(vas_med-Vc[ind]*Vdc);
//        icb_km1=(1-C1)*ibc_med + C2*(vbs_med-Vc[ind]*Vdc);
//        icc_km1=(1-C1)*icc_med + C2*(vcs_med-Vc[ind]*Vdc); 
       
       ica_km1=(1-C1)*iac_med + C2*(Vas_N -Vc[ind]*Vdc);
       icb_km1=(1-C1)*ibc_med + C2*(Vbs_N -Vc[ind]*Vdc);
       icc_km1=(1-C1)*icc_med + C2*(Vcs_N -Vc[ind]*Vdc);
       
    
       
       
//        vcap_a_km1 = dclink_1 + C3*iac_med*XI[ind];
//        vcap_b_km1 = dclink_2 + C3*ibc_med*XI[ind];
//        vcap_c_km1 = dclink_3 + C3*icc_med*XI[ind];
      
     

//Se calcula el error de seguimento de corriente 
// 	   dif_a = (ica_ref - ica_km1)*(ica_ref - ica_km1);
// 	   dif_b = (icb_ref - icb_km1)*(icb_ref - icb_km1);
//        dif_c = (icc_ref - icc_km1)*(icc_ref - icc_km1);
//        
//        
//        vcap_a_dif = (Vdc-vcap_a_km1)*(Vdc-vcap_a_km1);
//        vcap_b_dif = (Vdc-vcap_b_km1)*(Vdc-vcap_b_km1);
//        vcap_c_dif = (Vdc-vcap_c_km1)*(Vdc-vcap_c_km1);
// //        
// //        //Se calcula el valor de la función de coste
//        fc_Ja = sqrt(dif_a) + lamda*sqrt(vcap_a_dif);
//        fc_Jb = sqrt(dif_b) + lamda*sqrt(vcap_b_dif);
//        fc_Jc = sqrt(dif_c) + lamda*sqrt(vcap_c_dif);
       
       

     //Se calcula el error de seguimento de corriente 
	   dif_a = ica_ref - ica_km1;
	   dif_b = icb_ref - icb_km1;
       dif_c = icc_ref - icc_km1;
     //  Se calcula el valor de la función de coste
       fc_Ja = dif_a*dif_a;
       fc_Jb = dif_b*dif_b;
       fc_Jc = dif_c*dif_c; 

                
     //  Se evalua la función de coste
        if (fc_Ja < fc_Joa){
            fc_Joa = fc_Ja;
            ioa = ind;
            ica_km1_men = ica_km1;
            
            //ioa = vect;
            //io[0] = ioa;
        }
        
        if (fc_Jb < fc_Job){
            fc_Job = fc_Jb;
            iob = ind;
            icb_km1_men = icb_km1;
            
            //iob = vect;
            //io[1] = iob;
        }   
        
        if (fc_Jc < fc_Joc){
            fc_Joc = fc_Jc;
            ioc = ind;
            icc_km1_men = icc_km1;
            
            //ioc = vect;
            //io[2] = ioc;
        }
    
    
     }
    
        //referencias de tension
//     if(Vc[ioa]==3 || Vc[ioa]==-3){
//         if(cont1 == 5){
//          ioa = ioa-2;
//          cont1 = 0;
//         }
//         else{
//          cont1 = cont1+1;
//         }
//         vca_ref =Vc[ioa]*0.3333333333*0.9;
//         
//   
//     }
//     else{
//     
//        vca_ref =Vc[ioa]*0.3333333333;
//     }
//     
//         
//     if(Vc[iob]==3 || Vc[iob]==-3){
//         if(cont2 == 5){
//          iob = iob-2;
//          cont2 = 0;
//         }
//         else{
//          cont2 = cont2+1;
//         }
//          vcb_ref =Vc[iob]*0.3333333333*0.9;
//   
//     }
//     else{
//     
//         vcb_ref =Vc[iob]*0.3333333333;
//     }
//      
//     
//      if(Vc[ioc]==3 || Vc[ioc]==-3){
//         if(cont3 == 5){
//          ioc = ioc - 2;
//          cont3 = 0;
//         }
//         else{
//          cont3 = cont3+1;
//         }
//           vcc_ref =Vc[ioc]*0.3333333333*0.9;
//   
//     }
//     else{
//     
//          vcc_ref =Vc[ioc]*0.3333333333;
//     } 
    
        vca_ref =Vc[ioa]*0.3333333333;
        vcb_ref =Vc[iob]*0.3333333333;
        vcc_ref =Vc[ioc]*0.3333333333;
    
       
       

     // Indice de vectores optimos       
//        io[0] = ioa;
//        io[1] = iob;
//        io[2] = ioc;

    // funcion de costo   
       fc[0] = vca_ref;
       fc[1] = vcb_ref;
       fc[2] = vcc_ref;
    
   
    //Visualizacion de parametros
     
       Vs_alfabeta[0] = QS;
       Vs_alfabeta[1] = QL;
       
       PLQL[0] = PL;
       PLQL[1] = QL;
       
       Icref[0] = ica_ref;
       Icref[1] = icb_ref;
       Icref[2] = icc_ref;
        
       ic_km1[0] = ica_km1_men ;
       ic_km1[1] = icb_km1_men ;
       ic_km1[2] = icc_km1_men ;
       
       Varfiltro[0] = 02;
       Varfiltro[1] = err1;
       Varfiltro[2] = ica_bar;
       Varfiltro[3] = icb_bar;
       Varfiltro[4] = icc_bar;
       Varfiltro[5] = dclink_1;
       Varfiltro[6] = dclink_2;
       Varfiltro[7] = dclink_3;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


