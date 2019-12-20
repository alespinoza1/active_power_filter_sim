% /************************************************************************
%  File name   :	GlobalParam.m
%  Originator  : 	L. Comparatore
%  Description : 	Se declaran en este archivo todas las variables y
%                   constantes globales
% -------------------------------------------------------------------------
% =======================================================================*/
close all;
clear all;
clc;
%%%%%%%%%% DEFINICION DE VARIABLES GLOBALES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  Tm fm Ts Tsim  ... %Parametros de simulacion
        Vs VsLL fe we tetaa tetab tetac ... %Parametros de la red electrica
        Vdc Cdc Vodc Ideal Rdc...  %Parametros del DC-Link
        Ron Rs Cs ... %Parametros de los dispositivos semiconductores (IGBT/SiC-MOSFET) 
        Ron1 Rs1 Cs1 ... %Parametros de todos los switches ideales
        band ...
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %Control
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  tant ...
        ioa iob ioc ... 
        XI c Vc c1 ...%Parametros del CHB  
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %Control con PWM
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  nc ...

       
% =======================================================================*/


%% %%%%%%% PARAMETROS DE SIMULACION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fm = 5000; %Frecuencia de muestreo [Hz]
%fm = fm/2; %Frecuencia de muestreo [Hz] %para el M2PC
Tm = 1/fm; %Periodo de muestreo [s]
Tsim= Tm*800; %Tiempo total de simulacion [s]
%Ts= Tm/10; %Tiempo de integracion para la simulacion [s]
Ts= 1e-6;

%% %%%%%%% PARAMETROS DE LA RED ELECTRICA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vs= 220*sqrt(2);%Tension de la red [V]
VsLL= Vs*sqrt(3);
fe = 50; %Frecuencia de la red [Hz]
we= 2*pi*fe; %Frecuencia de la red [rad/s]
tetaa= 0; %Angulo de fase a [deg]
tetab= 240; %-120; %Angulo de fase b [deg]
tetac= 120; %Angulo de fase c [deg]


%% %%%%%%% PARAMETROS DEL DC-LINK %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vdc = Vs/3; %Tension ideal del DC-Link [V]
Cdc = 680e-6; %Capacitancia del DC-Link [F]
Vodc = Vdc; %Tension inicial en el capacitor [V]
Ideal = 1; %Variable que indica si el DC-Link es una fuente de tension ideal o un capacitor: 1 = Fuente ideal, 0 = Capacitor
Rdc=910e3; %Resistor de carga/descarga del capacitor (DC-Link)

%% %%%%%%% PARAMETROS DE LOS IGBT/SiC-MOSFET %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ron= 1e-3; %Internal resistance [Ohms]
Rs= 1e5; %Snubber resistance [Ohms]
Cs= 0.5; %Snubber capacitance [F]

%% %%%%%%% PARAMETROS DE LOS SWITCHERS IDEALES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ron1= 1e-3; %Internal resistance [Ohms]
Rs1= 1e5; %Snubber resistance [Ohms]
Cs1= inf; %Snubber capacitance [F]

%% %%%%%%%%%%%%% PARAMETROS DEL CHB %%%%%%%%%%%%%%%%%%%% 

nc = 3; %Nº de celdas por fase

%Definicion de los 64 posibles vectores de disparo/estados de conmutacion
XI=[    0 0 0 0 0 0;
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
        1 1 1 1 1 1;
        ]; %Matriz de estados de conmutacion
[c,n] = size(XI); %Cantidad de filas y columnas de la matriz de estados de conmutacion

%funciones de conmutacion correspondientes a los estados de conmutacion respectivamente
Vc = [0,-1,1,0,-1,-2,0,-1,1,0,2,1,0,-1,1,0,-1,-2,0,-1,-2,-3,-1,-2,0,-1,1,0,-1,-2,0,-1,1,0,2,1,0,-1,1,0,2,1,3,2,1,0,2,1,0,-1,1,0,-1,-2,0,-1,1,0,2,1,0,-1,1,0];
[c1,n1] = size(Vc); %Cantidad de filas y columnas del vector de funciones de conmutacion

%% %%%%%%%%%%%%% PARAMETROS DE CONTROL %%%%%%%%%%%%%%%%%%%% 
tant = 0; %Instante de la muestra anterior MBPC clasico

%Valores iniciales optimos
ioa = 1;
iob = 1;
ioc = 1;

%variable (bandera) auxiliar
band=1;

   