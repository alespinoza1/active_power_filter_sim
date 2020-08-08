format long
clear all
close all
pack
clc

% =======================================================================*/
%% %%%%%%%%%%%%% PARAMETROS DE CONTROL %%%%%%%%%%%%%%%%%%%% 
fs = 18000;
Ts = 1/fs;
Tm = 1e-6;

%DC-Link
Vdc = 63.0; %(V)
Cdc = 2480e-6; %(F)
fe = 50;
%% %%%%%%%%%%%%% PARAMETROS ELECTRICOS %%%%%%%%%%%%%%%%%%%% 

% Filtro de laboratorio
Rc = 0.35;
Lc = 10e-3;
RL = 23.232;
LL = 0.055462;


%% %%%%%%%%%%%%% ESTADOS DE CONMUTACI�N %%%%%%%%%%%%%%%%%%%% 

%Definicion de los 7 posibles vectores de disparo/estados de conmutacion: Matriz de estados de conmutacion   
    %XI=[0 1 0 1 0 1;
    %    0 0 0 1 0 1;
    %    0 0 0 0 0 1;
    %    0 0 0 0 0 0;
    %    0 0 0 0 1 0;
    %    0 0 1 0 1 0;
    %    1 0 1 0 1 0];
%[c,n] = size(XI); %Cantidad de filas y columnas de la matriz de estados de conmutacion
 %funciones de conmutacion correspondientes a los estados de conmutacion respectivamente
%Vc = [-3,-2,-1,0,1,2,3];% vector de niveles activos del CHB
 
%% %%%%%%%%%%%%% INICIALIZACI�N DE VARIABLES GLOBALES %%%%%%%%%%%%%%%%%%%% 

%Valores iniciales optimos
ioa = 0;
iob = 0;
ioc = 0;

ica_ref = 0;
icb_ref = 0;
icc_ref = 0;

ic_alpha=0;
ic_beta =0;

%PI
cnt_ciclos = 0;
Tm_pi = 1/1000;
PL=0;
PLkm2 = 0;
PLkm1 = 0;
QL=0;
PL0 = 0;
Pcbar = 0.0;
Pcbarkm2 = 0.0;
Pcbarkm1 = 0.0;
err = 0;
err_ant = 2;
upi = 0;
upi_ant = 0;
kp=0.007;
ki=0.006;
lamda = 0.02;
sat = 0;
cnt_ciclos = 0;

%%%%%%%%%%%%% PARAMETROS DEL FILTRO DE BUTTERWORTH 2do ORDEN %%%%%%%%%%%%%%%%%%%% 
fm_fd = 1000;        %Frecuenia de muestreo del LPF
fn = fm_fd/2;        %frecuencia de nyquist   
[N Wc] = buttord(25/fn,125/fn,1,20); % fc = 25Hz, fs = 125Hz, Gc = -1dB, Gp = -20dB
[num,den] = butter(N,Wc);
x=num(1);
y=num(2);
z=num(3);
e=den(1);
f=den(2);
g=den(3);


%Carga de valores iniciales

K = 10;

Vsa_offset = 1.507;
Vsb_offset = 1.466;
Vsc_offset = 1.495;

Ila_offset = 0.0;
Ilb_offset = 0.0; 
Ilc_offset = 0.0;

Ica_offset = 0.0;
Icb_offset = 0.0;
Icc_offset = 0.0;

Ganancia_Vsa = 250.0;
Ganancia_Vsb = 250.0;
Ganancia_Vsc = 250.0;

Ganancia_Ila = 2.7659*K;
Ganancia_Ilb = 2.7659*K;
Ganancia_Ilc = 2.7083*K;

Ganancia_Ica = 2.6804*K;
Ganancia_Icb = 2.7956*K;
Ganancia_Icc = 2.7659*K;

fc_Joa = 1000000;
fc_Job = 1000000;
fc_Joc = 1000000;

fc_Ja = 0;
fc_Jb = 0;
fc_Jc = 0;

isa = 0.0;
isb = 0.0;
isc = 0.0;

vca_ref = 0;
vcb_ref = 0;
vcc_ref = 0;

ica_ref = 0;
icb_ref =0;
icc_ref = 0;


vcap_a_km1 = 0.0;
vcap_b_km1 = 0.0;
vcap_c_km1 = 0.0;

vcap_a_dif = 0.0;
vcap_b_dif = 0.0;
vcap_c_dif = 0.0;
