format long
clear all
close all
pack
clc

%%%%%%%%%%%%%%%%%%%%%%
% Simulación Matrix Trifásico
% Voltage source (line to line rms value)
Vs = 15*sqrt(3); 
% Source frequency (Hz)
fs = 50;
% Ajuste de offset para los sensores
Ia_offset=0.1675;
Ib_offset=0.1675;
Ic_offset=0.1675;
Ganancia_Ioa=1;
Ganancia_Iob=1;
Ganancia_Ioc=1;

Vu_offset=0.0165;
Vv_offset=0.0165;
Vw_offset=0.0165;
Ganancia_Vu=345;
Ganancia_Vv=345;
Ganancia_Vw=345;
% 
Lf = 0.02996;%4700e-6;%400e-6;
Rf = 0.01;
Cf = 6.9e-6;%1.3528e-05%25e-6;
Rp=100;

R = 10;     % Load resistor
L = 0.026;  % Load inductor

Ts = 1/10000; % Sampling time
Iref = 1;     % Amplitude output current reference
fref = 50;    % Output frequency

lambda=0.00008;
vopt=0;
%% Parametros de simulacion y MPC 
simular = 0.1; % Simulation time

%% Modelo del sistema continuo
%% Modelo del sistema continuo
A=[-1/(Rp*Cf) 1/Cf;-1/Lf -Rf/Lf];
B=[1/(Rp*Cf) -1/Cf;1/Lf 0];
C=[1 0;-1/Rp 1];
D=[0 0;1/Rp 0];
sys_c=ss(A,B,C,D);
sys_d=c2d(sys_c,Ts);
Aq11 = sys_d.a(1,1);
Aq12 = sys_d.a(1,2);
Aq21 = sys_d.a(2,1);
Aq22 = sys_d.a(2,2);
Bq11 = sys_d.b(1,1);
Bq12 = sys_d.b(1,2);
Bq21 = sys_d.b(2,1);
Bq22 = sys_d.b(2,2);   