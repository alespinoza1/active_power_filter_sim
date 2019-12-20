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


clear all;

set(0,'DefaultTextInterpreter', 'none')% para borrar el interprete LATEX en caso de que se haya usado anteriormente

%%%%%%%%%% DEFINICION DE VARIABLES GLOBALES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  Tm fm Ts Tsim APFon ... %Parametros de simulacion
        Vs fe we tetaa tetab tetac ... %Parametros de la red electrica
        RL LL ... %Parametros de la carga
        Rf Lf ... %Parametros del filtro
        Vdc Cdc Vodc Ideal ...  %Parametros del DC-Link
        Ron Rs Cs ... %Parametros de los dispositivos semiconductores (IGBT/SiC-MOSFET) 
        Ron1 Rs1 Cs1 ... %Parametros de todos los switches ideales
        band ...
        ica_ref icb_ref icc_ref vca_ref vcb_ref vcc_ref Qref ... %Parametros de referencias
        lambda glevels indopt...
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %MBPC
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  tant ...
        ioa iob ioc ... 
        XI c Vc c1 ...%Parametros del CHB
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %MBPC con incremento del horizonte de prediccion
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  vca_refant vcb_refant vcc_refant ...    
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %MBPC con PWM
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  nc ...
        ma ...
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %MBPC con PWM del espacio de estados de conmutacion
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  tant1 tant2 tant3 ...
        ioa0 iob0 ioc0 ioa1 iob1 ioc1 ioa2 iob2 ioc2 ...
        Ta0 Ta1 Ta2 Tb0 Tb1 Tb2 Tc0 Tc1 Tc2... 
        SEC c2 lvs ctl ...
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %MBPC con conmutador de estados redundantes
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  tanton ...
        tona tonb tonc ...
        loa lob loc ...
        Soa Sob Soc ...
        L0 L1 L2 L3 L_1 L_2 L_3 cl0 cl1 cl2 cl3 lvs1 ctl1 ...
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %MBPC con PWM del espacio de estados de conmutacion y 
        %con conmutador de estados redundantes
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global  tona0 tonb0 tonc0 tona1 tonb1 tonc1 tona2 tonb2 tonc2...
        atanton1 atanton2 atanton3 atanton4 atanton5 atanton6 atanton7...
        btanton1 btanton2 btanton3 btanton4 btanton5 btanton6 btanton7...
        ctanton1 ctanton2 ctanton3 ctanton4 ctanton5 ctanton6 ctanton7...
        loa2 lob2 loc2 ...
        Soa0 Sob0 Soc0 Soa1 Sob1 Soc1 Soa2 Sob2 Soc2 ...
        vc1 vc2 vc3 ...
        SECN c3...
       
% =======================================================================*/


%% %%%%%%% PARAMETROS DE SIMULACION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fm = 10000; %Frecuencia de muestreo [Hz]
%fm = fm/2; %Frecuencia de muestreo [Hz] %para el M2PC
Tm = 1/fm; %Periodo de muestreo [s]
Tsim= 0.1; %Tiempo total de simulacion [s]
%Ts= Tm/10; %Tiempo de integracion para la simulacion [s]
Ts= 1e-6;
APFon = 0.02;%Tiempo de interconexion del APF con el sistema Carga-Red electrica [s]

%% %%%%%%% PARAMETROS DE LA RED ELECTRICA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vs= 310.2;%Tension de la red [V]
fe = 50; %Frecuencia de la red [Hz]
we= 2*pi*fe; %Frecuencia de la red [rad/s]
tetaa= 0; %Angulo de fase a [deg]
tetab= -120; %Angulo de fase b [deg]
tetac= 120; %Angulo de fase c [deg]

%% %%%%%%% PARAMETROS DE LA CARGA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
RL= 23.232; %Resistencia de carga [Ohms]
LL = 0.055462; %Inductancia de carga [H]

%% %%%%%%% PARAMETROS DEL FILTRO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Rf = 0.09; %Resistencia del filtro [Ohms]
Lf = 0.002996; %Inductancia del filtro [H]

%% %%%%%%% PARAMETROS DEL DC-LINK %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Vdc = 114; %Tension ideal del DC-Link [V]
Cdc = 680e-6; %Capacitancia del DC-Link [F]
Vodc = Vdc; %Tension inicial en el capacitor [V]
Ideal = 0; %Variable que indica si el DC-Link es una fuente de tension ideal o un capacitor: 1 = Fuente ideal, 0 = Capacitor

%% %%%%%%% PARAMETROS DE LOS IGBT/SiC-MOSFET %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ron= 1e-3; %Internal resistance [Ohms]
Rs= 1e5; %Snubber resistance [Ohms]
Cs= 0.5; %Snubber capacitance [F]

%% %%%%%%% PARAMETROS DE LOS SWITCHERS IDEALES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Ron1= 1e-3; %Internal resistance [Ohms]
Rs1= 1e5; %Snubber resistance [Ohms]
Cs1= inf; %Snubber capacitance [F]

%% %%%%%%%%%%%%% PARAMETROS DE REFERENCIAS %%%%%%%%%%%%%%%%%%%%
%Corrientes de referencias
ica_ref = 0;
icb_ref = 0;
icc_ref = 0;
%Tensiones de salida del CHB de referencias
vca_ref = 0;
vcb_ref = 0;
vcc_ref = 0;

vca_refant = 0;
vcb_refant = 0;
vcc_refant = 0;

%Potencia reactiva de referencia
Qref = 0;


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

%funciones de conmutacion de cada celda
vc1=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
vc2=[0,0,0,0,-1,-1,-1,-1,1,1,1,1,0,0,0,0,-1,-1,-1,-1,1,1,1,1,0,0,0,0,-1,-1,-1,-1,1,1,1,1,0,0,0,0,-1,-1,-1,-1,1,1,1,1,0,0,0,0,-1,-1,-1,-1,1,1,1,1,0,0,0,0];
vc3=[0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0,0,-1,1,0];

SEC=[2 3;
     3 5;
     5 6;
     6 8;
     8 9;
     9 11;
     11 12;
     12 14;
     14 15;
     15 17;
     17 18;
     18 20;
     20 21;
     21 22;
     22 23;
     23 24;
     24 26;
     26 27;
     27 29;
     29 30;
     30 32;
     32 33;
     33 35;
     35 36;
     36 38;
     38 39;
     39 41;
     41 42;
     42 43;
     43 44;
     44 45;
     45 47;
     47 48;
     48 50;
     50 51;
     51 53;
     53 54;
     54 56;
     56 57;
     57 59;
     59 60;
     60 62;
     62 63;
     63 2
     ]; %matriz de sectores de estados de conmutacion
 
 
[c2,n2] = size(SEC);%Cantidad de filas y columnas de la matriz de SECTORES de estados de conmutacion


%estados redundantes del nivel 0
L0=[    0 0 0 0 0 0;
        0 0 0 0 1 1;
        0 0 0 1 1 0;
        0 0 1 0 0 1;
        0 0 1 1 0 0;
        0 0 1 1 1 1;
        0 1 0 0 1 0;
        0 1 1 0 0 0;
        0 1 1 0 1 1;
        0 1 1 1 1 0;
        1 0 0 0 0 1;
        1 0 0 1 0 0;
        1 0 0 1 1 1;
        1 0 1 1 0 1;
        1 1 0 0 0 1;
        1 1 0 0 1 1;
        1 1 0 1 1 0;
        1 1 1 0 0 1;
        1 1 1 1 0 0;
        1 1 1 1 1 1;
        ];%matriz de estados de conmutacion redundantes del nivel 0
     
[cl0,nl0] = size(L0);%Cantidad de filas y columnas de la matriz de estados de conmutacion redundantes del nivel 0

%estados redundantes del nivel 1
L1=[    0 0 0 0 1 0;
        0 0 1 0 0 0;
        0 0 1 0 1 1;
        0 0 1 1 1 0;
        0 1 1 0 1 0;
        1 0 0 0 0 0;
        1 0 0 0 1 1;
        1 0 0 1 1 0;
        1 0 1 0 0 1;
        1 0 1 1 0 0;
        1 0 1 1 1 1;
        1 1 0 0 1 0;
        1 1 1 0 0 0;
        1 1 1 0 1 1;
        1 1 1 1 1 0;
        ];%matriz de estados de conmutacion redundantes del nivel 1
    
[cl1,nl1] = size(L1);%Cantidad de filas y columnas de la matriz de estados de conmutacion redundantes del nivel 1

%estados redundantes del nivel -1
L_1=[   0 0 0 0 0 1;
        0 0 0 1 0 0;
        0 0 0 1 1 1;
        0 0 1 1 0 1;
        0 1 0 0 0 0;
        0 1 0 0 1 1;
        0 1 0 1 1 0;
        0 1 1 0 0 1;
        0 1 1 1 0 0;
        0 1 1 1 1 1;
        1 0 0 1 0 1;
        1 1 0 0 0 1;
        1 1 0 1 0 0;
        1 1 0 1 1 1;
        1 1 1 1 0 1;
        ];%matriz de estados de conmutacion redundantes del nivel -1
    
%[cl_1,nl_1] = size(L_1);

%estados redundantes del nivel 2
L2=[    0 0 1 0 1 0;
        1 0 0 0 1 0;
        1 0 1 0 0 0;
        1 0 1 0 1 1;
        1 0 1 1 1 0;
        1 1 1 0 1 0;
        ];%matriz de estados de conmutacion redundantes del nivel 2
    
[cl2,nl2] = size(L2);%Cantidad de filas y columnas de la matriz de estados de conmutacion redundantes del nivel 2

%estados redundantes del nivel -2
L_2=[   0 0 0 1 0 1;
        0 1 0 0 0 1;
        0 1 0 1 0 0;
        0 1 0 1 1 1;
        0 1 1 1 0 1;
        1 1 0 1 0 1;
        ];%matriz de estados de conmutacion redundantes del nivel -2
    
%[cl_2,nl_2] = size(L_2);

%estados del nivel 3 y -3 respectivamente
L3=[    1 0 1 0 1 0;
        ];%matriz de estados de conmutacion redundantes del nivel 3

L_3=[   0 1 0 1 0 1;
        ];%matriz de estados de conmutacion redundantes del nivel -3

[cl3,nl3] = size(L3);%Cantidad de filas y columnas de la matriz de estados de conmutacion redundantes del nivel 3

%niveles activos del CHB 
lvs = [-3;-2;-1;1;2;3];% vector de niveles activos del CHB
%TOTAL DE NIVELES ACTIVOS
[ctl,ntl] = size(lvs);%Cantidad de filas y columnas del vector de niveles activos del CHB


%niveles del CHB 
lvs1 = [-3;-2;-1;0;1;2;3];% vector de niveles del CHB
%TOTAL DE NIVELES
[ctl1,ntl1] = size(lvs1);%Cantidad de filas y columnas del vector de niveles del CHB

%se usa con lvs
SECN=[1 2;
     2 3;
     3 4;
     4 5;
     5 6;
     6 1];
 
 
[c3,n3] = size(SECN);


%% %%%%%%%%%%%%% PARAMETROS DE CONTROL %%%%%%%%%%%%%%%%%%%% 
tant = 0; %Instante de la muestra anterior MBPC clasico

%Instantes de la muestra anterior M2PC 
tant1 =0; %fase a
tant2 =0; %fase b
tant3 =0; %fase c

%Instantes de la muestra anterior MBPC-SRS
tanton =0;

%Instantes de la muestra anterior M2PC-SRS
atanton1 =0;
atanton2 =0;
atanton3 =0;
atanton4 =0;
atanton5 =0;
atanton6 =0;
atanton7 =0;

btanton1 =0;
btanton2 =0;
btanton3 =0;
btanton4 =0;
btanton5 =0;
btanton6 =0;
btanton7 =0;

ctanton1 =0;
ctanton2 =0;
ctanton3 =0;
ctanton4 =0;
ctanton5 =0;
ctanton6 =0;
ctanton7 =0;

lambda = 0; %factor de peso de la funcion de costo

%tiempos de encendido
Ta0=0;
Ta1=0;
Ta2=0;
Tb0=0;
Tb1=0;
Tb2=0;
Tc0=0;
Tc1=0;
Tc2=0;


%cantidad de conmutaciones durante un periodo Tm
tona=cl0;
tonb=cl0;
tonc=cl0;

tona1=cl0;
tonb1=cl0;
tonc1=cl0;

tona2=cl0;
tonb2=cl0;
tonc2=cl0;

tona0=cl0;
tonb0=cl0;
tonc0=cl0;
%Valores iniciales optimos
ioa = 1;
iob = 1;
ioc = 1;
%indices optimos
ioa0 =1;
ioa1 =1;
ioa2=1;
iob0 =1;
iob1 =1;
iob2=1;
ioc0 =1;
ioc1 =1;
ioc2=1;

%niveles iniciales optimos
loa = 1;
lob = 1;
loc = 1;
loa2 = 1;
lob2 = 1;
loc2 = 1;

%matrices de niveles iniciales optimos
Soa = L0;
Sob = L0;
Soc = L0;

Soa0 = L0;
Sob0 = L0;
Soc0 = L0;

Soa1 = L0;
Sob1 = L0;
Soc1 = L0;

Soa2 = L0;
Sob2 = L0;
Soc2 = L0;

%variable (bandera) auxiliar
band=0;

%indices de modulacion
ma=[    0.5 0.5 0.5 0.5 0.5 0.5;        %1
        0.5 0.5 0.5 0.5 0 1;            %2
        0.5 0.5 0.5 0.5 1 0;            %3
        0.5 0.5 0.5 0.5 0.5 0.5;        %4
        0.5 0.5 0 1 0.5 0.5;            %5
        0.5 0.5 0 1 0 1;                %6
        0.5 0.5 0.5 0.5 0.5 0.5;        %7
        0.5 0.5 0 1 0.5 0.5;            %8
        0.5 0.5 1 0 0.5 0.5;            %9
        0.5 0.5 0.5 0.5 0.5 0.5;        %10
        0.5 0.5 1 0 1 0;                %11
        0.5 0.5 1 0 0.5 0.5;            %12
        0.5 0.5 0.5 0.5 0.5 0.5;        %13
        0.5 0.5 0.5 0.5 0 1;            %14
        0.5 0.5 0.5 0.5 1 0;            %15
        0.5 0.5 0.5 0.5 0.5 0.5;        %16
        0 1 0.5 0.5 0.5 0.5;            %17
        0 1 0.5 0.5 0 1;                %18
        0.5 0.5 0.5 0.5 0.5 0.5;        %19
        0 1 0.5 0.5 0.5 0.5;            %20
        0 1 0 1 0.5 0.5;                %21
        0 1 0 1 0 1;                    %22
        0 1 0 1 1 0                     %23
        0 1 0 1 0.5 0.5;                %24
        0.5 0.5 0.5 0.5 0.5 0.5;        %25
        0 1 1 0 0 1                     %26
        0 1 1 0 1 0                     %27
        0.5 0.5 0.5 0.5 0.5 0.5;        %28
        0 1 0.5 0.5 0.5 0.5;            %29
        0 1 0.5 0.5 0 1;                %30
        0.5 0.5 0.5 0.5 0.5 0.5;        %31
        0 1 0.5 0.5 0.5 0.5;            %32
        1 0 0.5 0.5 0.5 0.5;            %33
        0.5 0.5 0.5 0.5 0.5 0.5;        %34
        1 0 0.5 0.5 1 0;                %35
        1 0 0.5 0.5 0.5 0.5;            %36
        0.5 0.5 0.5 0.5 0.5 0.5;        %37
        1 0 0 1 0 1                     %38
        1 0 0 1 1 0                     %39
        0.5 0.5 0.5 0.5 0.5 0.5;        %40
        1 0 1 0 0.5 0.5;                %41
        1 0 1 0 0 1                     %42
        1 0 1 0 1 0                     %43
        1 0 1 0 0.5 0.5;                %44
        1 0 0.5 0.5 0.5 0.5;            %45
        0.5 0.5 0.5 0.5 0.5 0.5;        %46
        1 0 0.5 0.5 1 0;                %47
        1 0 0.5 0.5 0.5 0.5;            %48
        0.5 0.5 0.5 0.5 0.5 0.5;        %49
        0.5 0.5 0.5 0.5 0 1;            %50
        0.5 0.5 0.5 0.5 1 0;            %51
        0.5 0.5 0.5 0.5 0.5 0.5;        %52
        0.5 0.5 0 1 0.5 0.5;            %53
        0.5 0.5 0 1 0 1;                %54
        0.5 0.5 0.5 0.5 0.5 0.5;        %55
        0.5 0.5 0 1 0.5 0.5;            %56
        0.5 0.5 1 0 0.5 0.5;            %57
        0.5 0.5 0.5 0.5 0.5 0.5;        %58
        0.5 0.5 1 0 1 0;                %59
        0.5 0.5 1 0 0.5 0.5;            %60
        0.5 0.5 0.5 0.5 0.5 0.5;        %61
        0.5 0.5 0.5 0.5 0 1;            %62
        0.5 0.5 0.5 0.5 1 0;            %63
        0.5 0.5 0.5 0.5 0.5 0.5;        %64
        ]; %Matriz de indices de modulacion de amplitud para PWM Bipolar

   glevels=[0 0 0 0 0 0 0]; %funciones de costo de los 7 niveles
   indopt=[0 0 0 0 0 0 0]; %indices optimos de los 7 niveles
   