% /************************************************************************
%  File name   :	Staircase.m
%  Originator  : 	L. Comparatore
%  Description : 	Implementa el Staircase Modulation
%  Date        :    
% -------------------------------------------------------------------------
% =======================================================================*/
function [sal] = Staircase( ent )
global  Tm fm Ts Tsim  ... %Parametros de simulacion
        Vs fe we tetaa tetab tetac ... %Parametros de la red electrica
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
        theta1 theta2 theta3 delay1 delay2 delay3 time_pi time_2pi ...
        s11 s13 s21 s23 s31 s33 ...
    
tact = ent(1);

%CELDA 1 fase a
if (tact - tant) <= delay1
    s11 = 0;
    s13 = 0;
elseif (tact - tant) > delay1 && (tact - tant) <= (time_pi - delay1)
    s11 = 1;
    s13 = 0;
elseif (tact - tant) > (time_pi - delay1) && (tact - tant) <= (time_pi + delay1)
    s11 = 1;
    s13 = 1;
elseif (tact - tant) > (time_pi + delay1) && (tact - tant) <= (time_2pi - delay1)
    s11 = 0;
    s13 = 1;
elseif (tact - tant) > (time_2pi - delay1) && (tact - tant) < (time_2pi)
    s11 = 0;
    s13 = 0;  
end

%CELDA 2 fase a
if (tact - tant) <= delay2
    s21 = 0;
    s23 = 0;
elseif (tact - tant) > delay2 && (tact - tant) <= (time_pi - delay2)
    s21 = 1;
    s23 = 0;
elseif (tact - tant) > (time_pi - delay2) && (tact - tant) <= (time_pi + delay2)
    s21 = 1;
    s23 = 1;
elseif (tact - tant) > (time_pi + delay2) && (tact - tant) <= (time_2pi - delay2)
    s21 = 0;
    s23 = 1;
elseif (tact - tant) > (time_2pi - delay2) && (tact - tant) < (time_2pi)
    s21 = 0;
    s23 = 0;  
end

%CELDA 3 fase a
if (tact - tant) <= delay3
    s31 = 0;
    s33 = 0;
elseif (tact - tant) > delay3 && (tact - tant) <= (time_pi - delay3)
    s31 = 1;
    s33 = 0;
elseif (tact - tant) > (time_pi - delay3) && (tact - tant) <= (time_pi + delay3)
    s31 = 1;
    s33 = 1;
elseif (tact - tant) > (time_pi + delay3) && (tact - tant) <= (time_2pi - delay3)
    s31 = 0;
    s33 = 1;
elseif (tact - tant) > (time_2pi - delay3) && (tact - tant) < (time_2pi)
    s31 = 0;
    s33 = 0;  
end

%actualizacion de tant
if (tact - tant) >= time_2pi
tant = tact;
end

%salida
sal = [s11 s13 s21 s23 s31 s33];



