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
global Tm fm Ts Tsim APFon
fm = 15000; %Frecuencia de muestreo [Hz]
Tm = 1/fm; %Periodo de muestreo [s]
Tsim= 0.1; %Tiempo total de simulacion [s]
Ts= 1e-6; %Tiempo de integracion para la simulacion [s]
APFon = 0.02;%Tiempo de interconexion del APF con el sistema Carga-Red electrica [s]

%% parámetros de la red eléctrica %%
global Vs fe we teta_a teta_b teta_c 
Vs= 310.2;%Tension de la red [V]
fe = 50; %Frecuencia de la red [Hz]
we= 2*pi*fe; %Frecuencia de la red [rad/s]
teta_a= 0; %Angulo de fase a [deg]
teta_b= -120; %Angulo de fase b [deg]
teta_c= 120; %Angulo de fase c [deg]

%% parámetros del filtro de salida %%
global Rf Lf
Rf = 0.35; %Resistencia del filtro [Ohms]
Lf = 0.01; %Inductancia del filtro [H]

%% parámetros de la carga %%
global RL LL CL
RL= 23.232; %Resistencia de carga [Ohms]
LL = 0.055462; %Inductancia de carga [H]
CL = 2200; % capacitancia en [mF]

%% parámetros del convertidor multinivel %%
    %%parametros DC-LINK%%
    global Vdc Cdc Vodc Ideal 
    Vdc = 114; %Tension ideal del DC-Link [V]
    Cdc = 680e-6; %Capacitancia del DC-Link [F]
    Vodc = Vdc; %Tension inicial en el capacitor [V]
    Ideal = 0; %Variable que indica si el DC-Link es una fuente de tension ideal o un capacitor: 1 = Fuente ideal, 0 = Capacitor
    
    %% parámetros de los semiconductores SiC-Mosfet
    global Ron Rs Cs XI c Vc
    Ron= 1e-3; %Internal resistance [Ohms]
    Rs= 1e5; %Snubber resistance [Ohms]
    Cs= 0.5; %Snubber capacitance [F]
    
    %Definicion de los 64 posibles vectores de disparo/estados de conmutacion: Matriz de estados de conmutacion   
    XI=[0 0 0 0 0 0;
        0 0 0 0 0 1;
        0 0 0 0 1 0;
        0 0 0 0 1 1;
        0 0 0 1 0 0;
        0 0 0 1 0 1;
        0 0 0 1 1 0;
        0 0 0 1 1 1;
        0 0 1 0 0 0;
        0 0 1 0 0 1;
        0 0 1 0 1 0;
        0 0 1 0 1 1;
        0 0 1 1 0 0;
        0 0 1 1 0 1;
        0 0 1 1 1 0;
        0 0 1 1 1 1;
        0 1 0 0 0 0;
        0 1 0 0 0 1;
        0 1 0 0 1 0;
        0 1 0 0 1 1;
        0 1 0 1 0 0;
        0 1 0 1 0 1;
        0 1 0 1 1 0;
        0 1 0 1 1 1;
        0 1 1 0 0 0;
        0 1 1 0 0 1;
        0 1 1 0 1 0;
        0 1 1 0 1 1;
        0 1 1 1 0 0;
        0 1 1 1 0 1;
        0 1 1 1 1 0;
        0 1 1 1 1 1;
        1 0 0 0 0 0;
        1 0 0 0 0 1;
        1 0 0 0 1 0;
        1 0 0 0 1 1;
        1 0 0 1 0 0;
        1 0 0 1 0 1;
        1 0 0 1 1 0;
        1 0 0 1 1 1;
        1 0 1 0 0 0;
        1 0 1 0 0 1;
        1 0 1 0 1 0;
        1 0 1 0 1 1;
        1 0 1 1 0 0;
        1 0 1 1 0 1;
        1 0 1 1 1 0;
        1 0 1 1 1 1;
        1 1 0 0 0 0;
        1 1 0 0 0 1;
        1 1 0 0 1 0;
        1 1 0 0 1 1;
        1 1 0 1 0 0;
        1 1 0 1 0 1;
        1 1 0 1 1 0;
        1 1 0 1 1 1;
        1 1 1 0 0 0;
        1 1 1 0 0 1;
        1 1 1 0 1 0;
        1 1 1 0 1 1;
        1 1 1 1 0 0;
        1 1 1 1 0 1;
        1 1 1 1 1 0;
        1 1 1 1 1 1; ];
    [c,n] = size(XI); %Cantidad de filas y columnas de la matriz de estados de conmutacion
    %funciones de conmutacion correspondientes a los estados de conmutacion respectivamente
    Vc = [0,-1,1,0,-1,-2,0,-1,1,0,2,1,0,-1,1,0,-1,-2,0,-1,-2,-3,-1,-2,0,-1,1,0,-1,-2,0,-1,1,0,2,1,0,-1,1,0,2,1,3,2,1,0,2,1,0,-1,1,0,-1,-2,0,-1,1,0,2,1,0,-1,1,0];
    
    
%% PARAMETROS DE CONTROL %% 
global  tant ioa iob ioc vca_ref vcb_ref vcc_ref

tant = 0; %Instante de la muestra anterior MBPC clasico

%Valores iniciales optimos
ioa = 1;
iob = 1;
ioc = 1;
%Tensiones de salida del CHB de referencias
vca_ref = 0;
vcb_ref = 0;
vcc_ref = 0;


