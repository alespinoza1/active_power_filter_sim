double Ts;
float vas_med, vbs_med, vcs_med;
float ial_med, ibl_med, icl_med;
float iac_med, ibc_med, icc_med;
double Rc;
double Lc;
float Vdc;
float dclink_1, dclink_2, dclink_3;
float kp, ki;
float lamda;
float e, g, f, x, y, z;
float sat;

double isa, isb, isc;
float is_alpha, is_beta, is0;
float il_alpha, il_beta, il0;
float vs_alpha, vs_beta, vs0;
float PL, QL, PL0;
float PS, QS, PS0;

int cnt_ciclos;
float Tm_pi;
float Pbar, Pbarkm2, Pbarkm1, PLkm2, PLkm1;
float err, err_ant, upi, upi_ant;

float Pc, Qc, D;
float ic_alpha, ic_beta;
float ica_ref, icb_ref, icc_ref;

double C1, C2, C3;
double fc_Joa, fc_Job, fc_Joc;
int ioa, iob, ioc;
int ind;
int Vc_ind;
int Vc[7] = {-3, -2, -1, 0, 1, 2, 3};
float dclink_1_km1, dclink_2_km1, dclink_3_km1;
int XI[7][6] = {{0,1,0,1,0,1},
                {0,0,0,1,0,1},
                {0,0,0,0,0,1},
                {0,0,0,0,0,0},
                {0,0,0,0,1,0},
                {0,0,1,0,1,0},
                {1,0,1,0,1,0}};
float ica_km1, icb_km1, icc_km1;
float ica_km1_men,icb_km1_men ,icc_km1_men;
float dif_dclink_1, dif_dclink_2, dif_dclink_3;
double dif_a, dif_b, dif_c;
double fc_Joa, fc_Job, fc_Joc, fc_Ja, fc_Jb, fc_Jc;
float vca_ref, vcb_ref, vcc_ref;
float in[13];
float fc[3];

float vs_alphabeta[2];
float PLQL[2];

float Icref[3];

float ic_km1[3];
float Varfiltro[8];
float ica_bar, icb_bar, icc_bar;

//Carga de valores iniciales
int K;
float Vsa_offset;
float Vsb_offset;
float Vsc_offset;

float Ila_offset;
float Ilb_offset;
float Ilc_offset;

float Ica_offset;
float Icb_offset;
float Icc_offset;

float Ganancia_Vsa;
float Ganancia_Vsb;
float Ganancia_Vsc;

float Ganancia_Ila;
float Ganancia_Ilb;
float Ganancia_Ilc;

float Ganancia_Ica;
float Ganancia_Icb;
float Ganancia_Icc;
