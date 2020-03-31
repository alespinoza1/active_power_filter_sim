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
global Ron Rs Cs XI c nc Vc

%% PARAMETROS DE CONTROL %% 
global  tant ...
        ioa iob ioc ... 
        vca_ref vcb_ref vcc_ref ...
        ica_ref icb_ref icc_ref
    
%% PARAMETROS DEL FILTRO DIGITAL %%
global  Tm_fd fm_fd tant_fd xkm1 xkm2 ykm1 ykm2... %Parametros de simulacion
        num den %numerador y denominador del filtro digital
%% PARAMETROS DEL PID CONTROL %%    
global Tmpi kp ki tantpi  err_antpi resp_ant    
        
%% %%%%%%% SEÑALES DE ENTRADA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Instante actual
tact = x(1);
%Tensiones medidas en la red electrica
vas_med = x(2);
vbs_med = x(3);
vcs_med = x(4);
%Corrientes medidas en la carga
ial_med = x(5);
ibl_med = x(6);
icl_med = x(7);
%Corrientes medidas a la salida del APF
iac_med = x(8);
ibc_med = x(9);
icc_med = x(10);
% tension medida en el capacitor de la celda puente H
vcca = x(11)


%%%%%%%%% RUTINA DE CONTROL %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Se espera el tiempo de muestreo
if tact-tant >= Tm
    %% %%%%%%% GENERADOR DE REFERENCIA/S %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    %SE CONVIERTEN LAS CORRIENTES DE CARGA ABC A SU EQUIVALENTE EN PLANO AB
    il_alpha =  sqrt(2/3)*(ial_med-ibl_med/2-icl_med/2);
    il_beta = sqrt(2)*(ibl_med/2-icl_med/2);
    
    %SE CONVIERTEN LAS TENSIONES DE LA RED ABC A SU EQU EN EL PLANO AB
    vs_alpha =  sqrt(2/3)*(vas_med-vbs_med/2-vcs_med/2);
    vs_beta = sqrt(2)*(vbs_med/2-vcs_med/2);
    
    %SE CALCULAN LAS POTENCIAS ACTIVA Y REACTIVAS DE LA CARGA:
    PL = vs_alpha*il_alpha + vs_beta*il_beta;
    QL = vs_beta*il_alpha - vs_alpha*il_beta;
    
    %SE FILTRA LA POTENCIA ACTVIA Y COMPENSA LA CARGA DEL CAPACITOR:
    
    %Instante actual
    tact_fd = tact;
    %señal a filtrar
    xk =  PL;
    if (tact_fd-tant_fd) >= Tm_fd
        yk = ( num(1)*xk + num(2)*xkm1 + num(3)*xkm2 - den(2)*ykm1 - den(3)*ykm2 )/den(1);
        tant_fd = tact_fd;
        xkm2 = xkm1;
        xkm1 = xk;
        ykm2 = ykm1;
        ykm1 = yk;
    else
        yk = ykm1;
    end
    
    tact_pi = tact;
    referencia = Vdc*3;
    salida_med = vcca;

    if (tact_pi - tantpi) >= Tmpi
        err_act = referencia - salida_med;
        pid = resp_ant + kp*(err_act - err_antpi) + Tmpi*ki*err_act;
        resp_ant = pid;
        err_antpi = err_act;
        tantpi = tact_pi;
    else
        pid = resp_ant;
    end
    
    %SE ESTABLECEN LAS POTENCIAS QUE DEBE INYECTAR EL APF
    Pc = PL - yk - pid;
    Qc = QL;
   
    %VARIABLE AUXILIAR
    D = vs_alpha*vs_alpha + vs_beta*vs_beta;
    
    %SE CALCULAN LAS CORRIENTES DE REFERENCIAS EN EL PLANO AB
    ic_alpha = (vs_alpha*Pc + vs_beta*Qc)/D; 
    ic_beta = (vs_beta*Pc - vs_alpha*Qc)/D;
    
    %SE CONVIERTEN LAS CORRIENTES DE REFERENCIA DEL APF AB A SU EQUI EN ABC
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
    res=[vca_ref, vcb_ref, vcc_ref,ica_ref,icb_ref,icc_ref];

   
else

    res=[vca_ref, vcb_ref, vcc_ref,ica_ref,icb_ref,icc_ref];

end



