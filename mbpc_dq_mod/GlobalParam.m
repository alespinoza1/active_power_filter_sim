% /************************************************************************
%  File name   :	GlobalParam.m
%  Originator  : 	L. Comparatore
%  Modified by :    A. Espinoza
%  Description : 	Se declaran en este archivo todas las variables y
%                   constantes globales
% -------------------------------------------------------------------------
% =======================================================================*/
close all
clear all
clc

set(0,'DefaultTextInterpreter', 'none')% para borrar el interprete LATEX en caso de que se haya usado anteriormente

%%%%%%%%%% DEFINICION DE VARIABLES GLOBALES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% parámetros de simulación %%
global Tm fm Ts Tsim APFon fc 
fm = 20000; %Frecuencia de muestreo [Hz]
fc = 15000; % frecuencia de la portadora
Tm = 1/fm; %Periodo de muestreo [s]
Tsim= 1; %Tiempo total de simulacion [s]
Ts= 10e-6; %Tiempo de integracion para la simulacion [s]
APFon = 0.010;%Tiempo de interconexion del APF con el sistema Carga-Red electrica [s]


%% parámetros de la red eléctrica %%
global Vs fe we teta_a teta_b teta_c 
Vs= 120*sqrt(2);%Tension de la red [V]
fe = 50; %Frecuencia de la red [Hz]
we= 2*pi*fe; %Frecuencia de la red [rad/s]
teta_a= 0; %Angulo de fase a [deg]
teta_b= 120; %Angulo de fase b [deg]
teta_c= -120; %Angulo de fase c [deg]

%% parámetros del filtro de salida %%
global Rf Lf
Rf = 0.35; %Resistencia del filtro [Ohms]
Lf = 0.01; %Inductancia del filtro [H]

%% parámetros de la carga %%
global RL LL CL
RL= 23.232; %Resistencia de carga [Ohms]
LL = 0.055462; %Inductancia de carga [H]
CL = 2200e-6; % capacitancia en [mF]

%% parámetros del convertidor multinivel %%
    %%parametros DC-LINK%%
    global Vdc Cdc Vodc Ideal vcrls
    Vdc = 65; %Tension ideal del DC-Link [V]
    Cdc = 680e-6; %Capacitancia del DC-Link [F]
    Vodc = Vdc; %Tension inicial en el capacitor [V]
    Ideal = 0; %Variable que indica si el DC-Link es una fuente de tension ideal o un capacitor: 1 = Fuente ideal, 0 = Capacitor
    
    %% parámetros de los semiconductores SiC-Mosfet
    global Ron Rs Cs XI c Vc nc
    Ron= 1e-3; %Internal resistance [Ohms]
    Rs= 1e5; %Snubber resistance [Ohms]
    Cs= 0.5; %Snubber capacitance [F]
    
    nc = 3; %Nº de celdas por fase
    
    vcrls = 1/6;
    
    %Definicion de los 7 posibles vectores de disparo/estados de conmutacion: Matriz de estados de conmutacion   
    XI=[0 1 0 1 0 1;
        0 0 0 1 0 1;
        0 0 0 0 0 1;
        0 0 0 0 0 0;
        0 0 0 0 1 0;
        0 0 1 0 1 0;
        1 0 1 0 1 0; ];
    [c,n] = size(XI); %Cantidad de filas y columnas de la matriz de estados de conmutacion
    %funciones de conmutacion correspondientes a los estados de conmutacion respectivamente
    Vc = [-3,-2,-1,0,1,2,3];% vector de niveles activos del CHB
    
%% PARAMETROS DEL PLL DIGITAL %%
global fo Theta v_q_km1 ylfkm1 fn B0 B1
fo = 0;
fn = fe;
Theta = 0;
v_q_km1 = 0;
ylfkm1 = 0;
tset = 30e-3; %30ms tiempo de establecimiento
zeta = 0.7; %factor de amortiguamiento
delta = 0.05;% banda error 5%
wn = -(1/(tset*zeta))*log(delta/(1/sqrt(1-zeta^2)));
kipll = wn^2/Vs;
kppll = 2*zeta*wn/Vs;
B0 = (2*kppll+kipll*Tm)/2
B1 = -(2*kppll-kipll*Tm)/2


    
%% PARAMETROS DE CONTROL %% 
global  tant ioa iob ioc vca_ref vcb_ref vcc_ref  ica_ref icb_ref icc_ref 
global Tmpi kp ki tantpi  err_antpi resp_ant
ki = 0.0009;%0.0009;
kp = 0.0055;%0.0055;
Tmpi = 1/1000;
tantpi = 0;
resp_ant = 0;
err_antpi = 0;

global  Tm_fd fm_fd tant_fd xkm1d xkm2d ykm1d ykm2d... %Parametros de filtro digital
        num den xkm1q xkm2q ykm1q ykm2q... %numerador y denominador del filtro digital
    
    
    fm_fd = 1000;
    fn = fm_fd/2;
    Tm_fd = 1/fm_fd;
    [N Wc] = buttord(25/fn, 125/fn, 1, 20); % fc = 25Hz, fs = 125Hz, Gc = -1dB, Gp = -20dB
    [num den] = butter(N,Wc);
    %fvtool(num,den)
    tant_fd = 0; %Instante de la muestra anterior filtro digital
    xkm1d = 0;
    xkm2d = 0;
    ykm1d = 0;
    ykm2d = 0;
    xkm1q = 0;
    xkm2q = 0;
    ykm1q = 0;
    ykm2q = 0;

tant = 0; %Instante de la muestra anterior MBPC clasico

%Valores iniciales optimos
ioa = 1;
iob = 1;
ioc = 1;
%Tensiones de salida del CHB de referencias
vca_ref = 0;
vcb_ref = 0;
vcc_ref = 0;

ica_ref = 0;
icb_ref = 0;
icc_ref = 0;


