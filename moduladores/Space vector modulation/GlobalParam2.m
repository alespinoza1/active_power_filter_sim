% /************************************************************************
%  File name   :	GlobalParam2.m
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
global  nc ... % cantidad de celdas puente H por fase
        vcrps ...% amplitud de la portadora phase-shifted
        vcrls ...% amplitud de la portadora level-shifted
        theta1 theta2 theta3 delay1 delay2 delay3 time_pi time_2pi ... %angulos de conmutacion de las celdas, staircase
        s11 s13 s21 s23 s31 s33 ...
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %Control con space vector modulation
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
global  K ... % constante 
        e ... %numero de Euler o constante de Napier
        ioa1 iob1 ioc1 ioa2 iob2 ioc2 ...  
       
% =======================================================================*/


%% %%%%%%% PARAMETROS DE SIMULACION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%fm = 5000; %Frecuencia de muestreo [Hz]
fm = 50; %Frecuencia de muestreo [Hz]
%fm = fm/2; %Frecuencia de muestreo [Hz] %para el M2PC
Tm = 1/fm; %Periodo de muestreo [s]
Tsim= Tm*4; %Tiempo total de simulacion [s]
Ts= Tm/100; %Tiempo de integracion para la simulacion [s]
%Ts= 1e-6;

%% %%%%%%% PARAMETROS DE LA RED ELECTRICA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vs= 220*sqrt(2);%Tension de la red [V]
VsLL= Vs*sqrt(3); 
fe = 50; %Frecuencia de la red [Hz]
we= 2*pi*fe; %Frecuencia de la red [rad/s]
tetaa= 0; %Angulo de fase a [deg]
tetab= 240; %-120; %Angulo de fase b [deg]
tetac= 120; %Angulo de fase c [deg]


%% %%%%%%% PARAMETROS DEL DC-LINK %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vdc = Vs; %Tension ideal del DC-Link [V]
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

nc = 1; %Nº de celdas por fase

%Definicion de los 4 posibles vectores de disparo/estados de conmutacion
XI=[    0 0;
        0 1;
        1 0;
        1 1;
        ]; %Matriz de estados de conmutacion
[c,n] = size(XI); %Cantidad de filas y columnas de la matriz de estados de conmutacion

%funciones de conmutacion correspondientes a los estados de conmutacion respectivamente
Vc = [0,-1,1,0];
[c1,n1] = size(Vc); %Cantidad de filas y columnas del vector de funciones de conmutacion

%% %%%%%%%%%%%%% PARAMETROS DE CONTROL %%%%%%%%%%%%%%%%%%%% 
tant = 0; %Instante de la muestra anterior MBPC clasico

%Valores iniciales optimos
ioa = 1;
iob = 1;
ioc = 1;

ioa1 = 1;
iob1 = 1;
ioc1 = 1;

ioa2 = 1;
iob2 = 1;
ioc2 = 1;

%variable (bandera) auxiliar
band=1;

%% %%%%%%%%%%%%% PARAMETROS DE PWM %%%%%%%%%%%%%%%%%%%% 
vcrps = 1;
vcrls = 1/6;


%% %%%%%%%%%%%%% PARAMETROS DE STAIRCASE modulation %%%%%%%%%%%%%%%%%%%%
%thetas = angulos(ma);
%theta1 = thetas(1);
%theta2 = thetas(2);
%theta3 = thetas(3);

%Angulos para ma=0.4
%theta1 = 89.1178;
%theta2 = 65.4203;
%theta3 = 40.6227;

%Angulos para ma=0.7
%theta1 = 64.5379;
%theta2 = 44.5646;
%theta3 = 18.6211;

%Angulos para ma=0.8
theta1 = 57.106;
theta2 = 28.717;
theta3 = 11.504;

%Angulos para ma=1.0
%theta1 = 0;
%theta2 = 0;
%theta3 = 0;

delay1 = (theta1/360)*Tm;
delay2 = (theta2/360)*Tm;
delay3 = (theta3/360)*Tm;

%time_pi= (180/360)*Tm;
time_pi= Tm/2 ;
time_2pi= Tm;


s11=0;
s13=0;
s21=0;
s23=0;
s31=0;
s33=0;



%K=1/3; %amplitud invariante
K=2/3; %amplitud invariante
%K= sqrt(2/3); %potencia invariante
%K=1;

e = 2.718281828459045235360; %numero de Euler o constante de Napier



