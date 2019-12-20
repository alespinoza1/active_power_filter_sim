% /************************************************************************
%  File name   :	MBPC.m
%  Originator  : 	L. Comparatore
%  Modified by :    A. Espinoza
%  Description : 	Implementa el MBPC clasico
% -------------------------------------------------------------------------
% =======================================================================*/
function [res] = MBPC( x )
%% parámetros de simulación %%
global Tm fm Ts Tsim APFon

%% parámetros de la red eléctrica %%
global Vs fe we teta_a teta_b teta_c

%% parámetros del filtro de salida %%
global Rf Lf

%% parámetros de la carga %%
global RL LL CL

%%parametros DC-LINK%%
global Vdc Cdc Vodc Ideal 

%% parámetros de los semiconductores SiC-Mosfet
global Ron Rs Cs XI c Vc

%% PARAMETROS DE CONTROL %% 
global  tant ...
        ioa iob ioc ... 
        vca_ref vcb_ref vcc_ref
        
%% %%%%%%% SEÑALES DE ENTRADA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Instante actual
tact = x(1);

%Corrientes de referencias 
ica_ref = x(2);
icb_ref = x(3);
icc_ref = x(4);
%Corrientes medidas a la salida del APF
iac_med = x(5);
ibc_med = x(6);
icc_med = x(7);
%Tensiones medidas en la red electrica
vas_med = x(8);
vbs_med = x(9);
vcs_med = x(10);

%% %%%%%%% RUTINA DE CONTROL %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Se espera el tiempo de muestreo
if tact-tant >= Tm 
    
    %% valores iniciales óptimos
    fc_Joa = 1e8; fc_Job = 1e8; fc_Joc = 1e8; %Inicializacion de Funciones de costo optimos
    ioa = 1; iob = 1; ioc = 1; %Inicializacion de indices optimos
    %Proceso de optimizacion
    for ind=1:c
        
        %tension de salida del CHB para el estado "ind"
        vc_ref =Vc(1,ind)*Vdc;
        
        %corrientes predichas a la salida de cada  fase del apf 
        ica_km1=(1-Tm*Rf/Lf)*iac_med + Tm/Lf*(vc_ref-vas_med);
        icb_km1=(1-Tm*Rf/Lf)*ibc_med + Tm/Lf*(vc_ref-vbs_med);
        icc_km1=(1-Tm*Rf/Lf)*icc_med + Tm/Lf*(vc_ref-vcs_med);
        
        %Se calcula el error de seguimiento de corriente
        dif_a = (ica_ref - ica_km1);
		dif_b = (icb_ref - icb_km1);
        dif_c = (icc_ref - icc_km1);
		
        fc_Ja = dif_a*dif_a;
        fc_Jb = dif_b*dif_b;
        fc_Jc = dif_c*dif_c;
        
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
    res=[XI(ioa,:), XI(iob,:), XI(ioc,:), vca_ref, vcb_ref, vcc_ref];

   
else

    res=[XI(ioa,:), XI(iob,:), XI(ioc,:), vca_ref, vcb_ref, vcc_ref];

end



