% /************************************************************************
%  File name   :	SVModulation.m
%  Originator  : 	L. Comparatore
%  Description : 	Implementa el Space Vector Modulation
%  Date        :    
% -------------------------------------------------------------------------
% =======================================================================*/
function [sal] = SVModulation( ent )
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
        ioa1 iob1 ioc1 ioa2  ioc2 ...  
   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
%entradas
tact = ent(1);
vcaref= ent(2);
vcbref= ent(3);
vccref= ent(4);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%se espera el periodo de muestreo
if (tact - tant) >= Tm
    %se calculan las tensiones linea a linea
    vcAB = vcaref -vcbref;  
    vcBC = vcbref -vccref;
    vcCA = vccref -vcaref;
    %se calula el vector espacial resultante de referencia
    vcref = K*(vcAB + vcBC*e^(2/3*pi*1i) + vcCA*e^(4/3*pi*1i));
    %parte real (alfa) del vector de referencia
    %vcalfaref= vcAB;
    %parte imaginaria (beta) del vector de referencia
    vcbetaref= (vcBC-vcCA)*sqrt(3)/3;
    %angulo de vcref
    angref =  abs(angle(vcref)*180/pi);
    %se verifica en que sector cae el vector de referencia
    if (vcbetaref>=0)
      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      if angref >=0 && angref <30
          sector=1; %definir como global
      elseif angref >=30 && angref <60
          sector=2;
      elseif angref >=60 && angref <90
          sector=3;
      elseif angref >=90 && angref <120
          sector=4;
      elseif angref >=120 && angref <150
          sector=5;
      elseif angref >=150 && angref <=180
          sector=6;
      end
      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    else % if (vcbetaref < 0)
     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      if angref >=0 && angref <30
          sector=12;
      elseif angref >=30 && angref <60
          sector=11;
      elseif angref >=60 && angref <90
          sector=10;
      elseif angref >=90 && angref <120
          sector=9;
      elseif angref >=120 && angref <150
          sector=8;
      elseif angref >=150 && angref <=180
          sector=7;
      end
      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
    end
%calculo de ciclos de trabajo


T0 = Tm -T1 -T2;%definir como global
%actualizacion de estados anteriores
tant = tact;
end

%la secuencia de conmutacion
if (tact - tant) < T0/4
    %aplicar vector nulo
    sal=[0 0 0 0 0 0];
end
if (tact - tant) >= T0/4 && (tact - tant) < T0/4+T1/2
    %aplicar vector UNO
end
if (tact - tant) >= T0/4+T1/2 && (tact - tant) < T0/4+T1/2+T2/2
    %aplicar vector DOS
end






