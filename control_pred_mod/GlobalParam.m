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
fm = 15000; %Frecuencia de muestreo [Hz]
fc = 15000; % frecuencia de la portadora
Tm = 1/fm; %Periodo de muestreo [s]
Tsim= 0.25; %Tiempo total de simulacion [s]
Ts= 10e-6; %Tiempo de integracion para la simulacion [s]
APFon = 0.015;%Tiempo de interconexion del APF con el sistema Carga-Red electrica [s]


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
    Vdc = 62; %Tension ideal del DC-Link [V]
    Cdc = 680e-6; %Capacitancia del DC-Link [F]
    Vodc = Vdc; %Tension inicial en el capacitor [V]
    Ideal = 1; %Variable que indica si el DC-Link es una fuente de tension ideal o un capacitor: 1 = Fuente ideal, 0 = Capacitor
    
    %% parámetros de los semiconductores SiC-Mosfet
    global Ron Rs Cs XI c Vc nc
    nc = 3; %Nº de celdas por fase
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
        1 0 1 0 1 0];
    [c,n] = size(XI); %Cantidad de filas y columnas de la matriz de estados de conmutacion
    %funciones de conmutacion correspondientes a los estados de conmutacion respectivamente
    Vc = [-3,-2,-1,0,1,2,3];% vector de niveles activos del CHB
    
    
%% PARAMETROS DE CONTROL %% 
global  tant ioa iob ioc vca_ref vcb_ref vcc_ref
global Tmpi Kp Ki tantpi  err_antpi resp_ant

Kp = 0.006;
Ki = 0.007;
Tmpi = 1/5000;
tantpi = 0;
resp_ant = 0;
err_antpi = 0;



tant = 0; %Instante de la muestra anterior MBPC clasico

%Valores iniciales optimos
ioa = 1;
iob = 1;
ioc = 1;
%Tensiones de salida del CHB de referencias
vca_ref = 0;
vcb_ref = 0;
vcc_ref = 0;


