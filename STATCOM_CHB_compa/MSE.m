% /************************************************************************
%  File name   :	MSE.m
%  Originator  : 	L. Comparatore
%  Description : 	Se recuperan los datos de las simulaciones para
%                   proceder a realizar el Error Cuadratico Medio de
%                   seguimiento de corriente
%
% -------------------------------------------------------------------------
% =======================================================================*/

clc

% cantidad total de muestras (Tsim/Ts +1)
%muestras = length(Ica_r);

% Se trunca a la porcion de interes y se genera el vector tiempo (desede el instante APFon hasta dos ciclos de fe Hz)
StartTime = 0.03;

a=StartTime/Ts +1; %primera muestra (en el instante start_time)
%b=muestras;
b= (StartTime + ((1/fe)*2) )/Ts +1; %ultima muestra


%Calculo del error cuadratico medio
ECMa = sqrt(sum(power(Ica_r(a:b, 1)-Ica_m(a:b, 1),2))/((b-a)+1))
ECMb = sqrt(sum(power(Icb_r(a:b, 1)-Icb_m(a:b, 1),2))/((b-a)+1))
ECMc = sqrt(sum(power(Icc_r(a:b, 1)-Icc_m(a:b, 1),2))/((b-a)+1))