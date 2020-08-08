
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
void Control_APF7_algoritmo_Outputs_wrapper(const real_T *in,
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
/*%%% Lectura de variables %%%*/

Ts = in[0];

vas_med = in[1];
vbs_med = in[2];
vcs_med = in[3];

ial_med = in[4];
ibl_med = in[5];
icl_med = in[6];

iac_med = in[7];
ibc_med = in[8];
icc_med = in[9];

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

//%%%%%%%%%%%%%%%%%%%%% GENERADOR DE REFERENCIA/S %%%%%%%%%%%%%%%%%%%%%
//Calculo corriente de linea
isa = ial_med - iac_med;
isb = ibl_med - ibc_med;
isc = icl_med - icc_med;

//SE CONVIERTEN LAS CORRIENTES DE RED ABC A SU EQUIVALENTE EN PLANO AB
is_alpha = 0.81649 * (isa - isb * 0.5 - isc * 0.5);
is_beta = 0.70711 * (isb - isc);
is0 = 0.57735 * (isa + isb + isc);

//SE CONVIERTEN LAS CORRIENTES DE CARGA ABC A SU EQUIVALENTE EN PLANO AB
il_alpha = 0.81649 * (ial_med - ibl_med * 0.5 - icl_med * 0.5);
il_beta = 0.70711 * (ibl_med - icl_med);
il0 = 0.57735 * (ial_med + ibl_med + icl_med);

//SE CONVIERTEN LAS TENSIONES DE LA RED ABC A SU EQU EN EL PLANO AB
vs_alpha = 0.81649658 * (vas_med - vbs_med * 0.5 - vcs_med * 0.5);
vs_beta = 0.707106781 * (vbs_med - vcs_med);
vs0 = 0.57735 * (vas_med + vbs_med + vcs_med);

//SE CALCULAN LAS POTENCIAS ACTIVA Y REACTIVAS DE LA CARGA
PL = vs_alpha * il_alpha + vs_beta * il_beta;
QL = vs_alpha * il_beta - vs_beta * il_alpha;
PL0 = vs0 * il0;

//SE CALCULAN LAS POTENCIAS ACTIVA Y REACTIVAS DE LA RED
PS = vs_alpha * is_alpha + vs_beta * is_beta;
QS = vs_alpha * is_beta - vs_beta * is_alpha;
PS0 = vs0 * is0;
//SE FILTRA LA POTENCIA ACTVA Y SE COMPENSA LA CARGA DEL CAPACITOR:
if (cnt_ciclos == 18)
{
    //Se implementa el LPF de butterworth de 2do orden con una frecuencia de corte fc
    Pbar = (x * PL + y * PLkm1 + z * PLkm2 - f * Pbarkm1 - g * Pbarkm2) / e;
    Pbarkm2 = Pbarkm1;
    Pbarkm1 = Pbar;
    PLkm2 = PLkm1;
    PLkm1 = PL;
    //Se implementa el control PI del Dc link asumiendo que se miden solo 3 Vdc
    err = Vdc - (dclink_1 + dclink_2 + dclink_3) / 3;
    upi = upi_ant + kp * (err - err_ant) + Tm_pi * ki * err;
    upi_ant = upi;
    err_ant = err;

    // SE PONEN EN CERO EL CONTADOR DE CICLOS
    cnt_ciclos = 0;
}
else
{
    Pbar = Pbarkm1;
    upi = upi_ant;
}

//SE ESTABLECEN LAS POTENCIAS QUE DEBE INYECTAR EL APF
// Pc = PL - Pbar - upi;
Pc = upi;
Qc = -QL;
//VARIABLE AUXILIAR
D = vs_alpha * vs_alpha + vs_beta * vs_beta;

//SE CALCULAN LAS CORRIENTES DE REFERENCIAS EN EL PLANO AB
ic_alpha = (vs_alpha * Pc + vs_beta * Qc) / D;
ic_beta = (vs_beta * Pc - vs_alpha * Qc) / D;

//SE CONVIERTEN LAS CORRIENTES DE REFERENCIA DEL APF AB A SU EQUI EN ABC
ica_ref = 0.81649658 * ic_alpha;
icb_ref = 0.81649658 * (-ic_alpha * 0.5 + 0.866025403 * ic_beta);
icc_ref = 0.81649658 * (-ic_alpha * 0.5 - 0.866025403 * ic_beta);

//%%%%%%%%%%%%%%%%%%%%% FIN GENERADOR DE REFERENCIA/S %%%%%%%%%%%%%%%%%%%%%

//%%%%%%%%%%%%%%%%%%%%% INICIO OPTIMIZACIÓN %%%%%%%%%%%%%%%%%%%%%
//uso de coef para eviar calculos repetidos;
C1 = Ts * 35;  // Ts*(Rc/Lc)
C2 = Ts * 100; // Ts*(1/Lc)
C3 = Ts * 403.2258; // Ts/C

//inicialización de función de costo
fc_Joa = 1e8;
fc_Job = 1e8;
fc_Joc = 1e8;

//inicialización de indices optimos
ioa = 0;
iob = 0;
ioc = 0;

//Se recorre la matriz de disparos
for (ind = 0; ind < 7; ind++)
{
    Vc_ind = Vc[ind] * Vdc;

    dclink_1_km1 = dclink_1 + C3 * iac_med * (XI[ind][1] - XI[ind][2]);
    dclink_2_km1 = dclink_2 + C3 * iac_med * (XI[ind][3] - XI[ind][4]);
    dclink_3_km1 = dclink_3 + C3 * iac_med * (XI[ind][5] - XI[ind][6]);

    //corrientes predichas a la salida de cada  fase del apf
    ica_km1 = (1 - C1) * iac_med + C2 * (Vc_ind - vas_med);
    icb_km1 = (1 - C1) * ibc_med + C2 * (Vc_ind - vbs_med);
    icc_km1 = (1 - C1) * icc_med + C2 * (Vc_ind - vcs_med);

    //Se calcula el error de seguimento del dclink
    dif_dclink_1 = (Vdc - dclink_1_km1);
    dif_dclink_2 = (Vdc - dclink_2_km1);
    dif_dclink_3 = (Vdc - dclink_3_km1);

    //Se calcula el error de seguimento de corriente
    dif_a = ica_ref - ica_km1;
    dif_b = icb_ref - icb_km1;
    dif_c = icc_ref - icc_km1;

    //Se calcula el valor de la función de coste
    fc_Ja = dif_a * dif_a + lamda * dif_dclink_1 * dif_dclink_1;
    fc_Jb = dif_b * dif_b + lamda * dif_dclink_2 * dif_dclink_2;
    fc_Jc = dif_c * dif_c + lamda * dif_dclink_3 * dif_dclink_3;

    // Se evalua la función de coste
    if (fc_Ja < fc_Joa)
    {
        fc_Joa = fc_Ja;
        ioa = ind;
        ica_km1_men = ica_km1;
    }

    if (fc_Jb < fc_Job)
    {
        fc_Job = fc_Jb;
        iob = ind;
        icb_km1_men = icb_km1;
    }

    if (fc_Jc < fc_Joc)
    {
        fc_Joc = fc_Jc;
        ioc = ind;
        icc_km1_men = icc_km1;
    }
}

vca_ref = Vc[ioa] * 0.3333333333;
vcb_ref = Vc[iob] * 0.3333333333;
vcc_ref = Vc[ioc] * 0.3333333333;

// funcion de costo
fc[0] = vca_ref;
fc[1] = vcb_ref;
fc[2] = vcc_ref;

//Visualizacion de parametros

Vs_alfabeta[0] = PS;
Vs_alfabeta[1] = QS;

PLQL[0] = PL;
PLQL[1] = QL;

Icref[0] = ica_ref;
Icref[1] = icb_ref;
Icref[2] = icc_ref;

//ic_km1[0] = ica_km1;
//ic_km1[1] = icb_km1;
//ic_km1[2] = icc_km1;

ic_km1[0] = ica_km1_men ;
ic_km1[1] = icb_km1_men ;
ic_km1[2] = icc_km1_men ;

Varfiltro[0] = 01;
Varfiltro[1] = Pc;
Varfiltro[2] = ica_bar;
Varfiltro[3] = icb_bar;
Varfiltro[4] = icc_bar;
Varfiltro[5] = dclink_1;
Varfiltro[6] = dclink_2;
Varfiltro[7] = dclink_3;

cnt_ciclos = cnt_ciclos + 1;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


