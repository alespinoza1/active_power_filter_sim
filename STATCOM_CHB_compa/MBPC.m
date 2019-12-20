% /************************************************************************
%  File name   :	MBPC.m
%  Originator  : 	L. Comparatore
%  Description : 	Implementa el MBPC clasico
% -------------------------------------------------------------------------
% =======================================================================*/
function [res] = MBPC( x )
global  Tm fm Ts Tsim APFon ... %Parametros de simulacion
        Vs fe we tetaa tetab tetac ... %Parametros de la red electrica
        RL LL ... %Parametros de la carga
        Rf Lf ... %Parametros del filtro
        Vdc Cdc Vodc Ideal ...  %Parametros del DC-Link
        Ron Rs Cs ... %Parametros de los dispositivos semiconductores (IGBT/SiC-MOSFET) 
        Ron1 Rs1 Cs1 ... %Parametros de todos los switches ideales
        band ...
        ica_ref icb_ref icc_ref vca_ref vcb_ref vcc_ref Qref ... %Parametros de referencias
        lambda ...
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
        m ...
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
        
%% %%%%%%% SEÑALES DE ENTRADA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Instante actual
tact = x(1);
%Potencia reactiva de referencia
Q_ref = x(2);
%Corrientes medidas en la carga
ial_med = x(3);
ibl_med = x(4);
icl_med = x(5);
%Corrientes medidas a la salida del APF
iac_med = x(6);
ibc_med = x(7);
icc_med = x(8);
%Tensiones medidas en la red electrica
vas_med = x(9);
vbs_med = x(10);
vcs_med = x(11);
%Tensiones medidas a la salida del CHB
%vac_med = x(12);
%vbc_med = x(13);
%vcc_med = x(14);


%% %%%%%%% RUTINA DE CONTROL %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Se espera el tiempo de muestreo
if tact-tant >= Tm,    
    %% %%%%%%% GENERADOR DE REFERENCIA/S %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %Se convierte las corrientes de carga abc a su equivalente en el plano alfa-beta
    il_alpha =  sqrt(2/3)*(ial_med-ibl_med/2-icl_med/2);
    il_beta = sqrt(2)*(ibl_med/2-icl_med/2);
    %Se convierte las tensiones de la red abc a su equivalente en el plano alfa-beta
    vs_alpha =  sqrt(2/3)*(vas_med-vbs_med/2-vcs_med/2);
    vs_beta = sqrt(2)*(vbs_med/2-vcs_med/2);
    %Se calculan las potencias activa y  reactiva de la carga
    %PL = vs_alpha*il_alpha + vs_beta*il_beta;
    QL = vs_beta*il_alpha - vs_alpha*il_beta;
    %Se establecen las potencias que debe inyectar el APF
    Pc = 0;
    Qc = -QL + Q_ref;
    %variable auxiliar
    D = vs_alpha*vs_alpha + vs_beta*vs_beta;
    %Se calculan las corrientes de referencia del APF en el plano alfa-beta
    ic_alpha = (vs_alpha*Pc + vs_beta*Qc)/D; 
    ic_beta = (vs_beta*Pc - vs_alpha*Qc)/D;
    %Se convierte las corrientes de referencia del APF alfa-beta a su equivalente en el plano abc
    ica_ref=  sqrt(2/3)*ic_alpha;
    icb_ref=  sqrt(2/3)*(-ic_alpha/2 + sqrt(3)/2*ic_beta);
    icc_ref=  sqrt(2/3)*(-ic_alpha/2 - sqrt(3)/2*ic_beta); 
    %% %%%%%%% FIN GENERADOR DE REFERENCIA/S %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% valores iniciales óptimos
    fc_Joa = 1e8; fc_Job = 1e8; fc_Joc = 1e8; %Inicializacion de Funciones de costo optimos
    ioa = 1; iob = 1; ioc = 1; %Inicializacion de indices optimos
    %Proceso de optimizacion
    for ind=1:c
        %tension de salida del CHB para el estado "ind"
        vc_ref =Vc(1,ind)*Vdc;
        %F1 = vc1(1,ind);
        %F2 = vc2(1,ind);
        %F3 = vc3(1,ind);
        %corrientes predichas a la salida de cada  fase del apf 
        ica_km1=(1-Tm*Rf/Lf)*iac_med + Tm/Lf*(vas_med-vc_ref);
        icb_km1=(1-Tm*Rf/Lf)*ibc_med + Tm/Lf*(vbs_med-vc_ref);
        icc_km1=(1-Tm*Rf/Lf)*icc_med + Tm/Lf*(vcs_med-vc_ref);
        %voltajes predichos a la salida de cada  fase del apf
        %vca_km1 = vac_med + (1/Cdc)*iac_med*Tm*Vc(1,ind);
        %vcb_km1 = vbc_med + (1/Cdc)*iac_med*Tm*Vc(1,ind);
        %vcc_km1 = vcc_med + (1/Cdc)*iac_med*Tm*Vc(1,ind);
        %Se calcula el error de seguimiento de corriente
        dif_a = (ica_ref - ica_km1);
		dif_b = (icb_ref - icb_km1);
        dif_c = (icc_ref - icc_km1);
		%dif_a = (ica_ref - ica_km1)/ica_ref;
		%dif_b = (icb_ref - icb_km1)/icb_ref;
        %dif_c = (icc_ref - icc_km1)/icc_ref;
        %Error del balance de tension
        %dif_va = (vca_ref - vca_km1)/vc_ref;
        %dif_vb = (vcb_ref - vcb_km1)/vc_ref;
        %dif_vc = (vcc_ref - vcc_km1)/vc_ref;
        %Se calcula el valor de la función de coste
        fc_Ja = dif_a*dif_a;
        fc_Jb = dif_b*dif_b; 
        fc_Jc = dif_c*dif_c;
        %fc_Ja = dif_a*dif_a + lambda*(dif_va*dif_va);
        %fc_Jb = dif_b*dif_b + lambda*(dif_vb*dif_vb); 
        %fc_Jc = dif_c*dif_c + lambda*(dif_vc*dif_vc);    
        
        if fc_Ja < fc_Joa
            fc_Joa = fc_Ja;
            ioa = ind; 
        end
        
        if fc_Jb < fc_Job
            fc_Job = fc_Jb;
            iob = ind;
            
        end
        if fc_Jc < fc_Joc
            fc_Joc = fc_Jc;
            ioc = ind;                    
        end
        
        %referencias de tension
        vca_ref =Vc(1,ioa)*Vdc;
        vcb_ref =Vc(1,iob)*Vdc;
        vcc_ref =Vc(1,ioc)*Vdc;
  
    end

    %actualizacion de estados anteriores
    tant = tact;
    %salida
    %res=[XI(ioa,:), XI(iob,:), XI(ioc,:), ica_ref, icb_ref, icc_ref];
    res=[XI(ioa,:), XI(iob,:), XI(ioc,:), ica_ref, icb_ref, icc_ref, vca_ref, vcb_ref, vcc_ref];

   
else
    %salida
    %res=[XI(ioa,:), XI(iob,:), XI(ioc,:), ica_ref, icb_ref, icc_ref];
    res=[XI(ioa,:), XI(iob,:), XI(ioc,:), ica_ref, icb_ref, icc_ref, vca_ref, vcb_ref, vcc_ref];

end



