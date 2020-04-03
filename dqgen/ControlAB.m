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

%% PARAMETROS DE CONTROL MBPC%% 
global  tant ...
        ioa iob ioc ... 
        vca_ref vcb_ref vcc_ref ...
        ica_ref icb_ref icc_ref
    
%% PARAMETROS DEL PLL DIGITAL %%
global fo fn Theta v_q_km1 ylfkm1 B0 B1

global  Tm_fd fm_fd tant_fd xkm1d xkm2d ykm1d ykm2d... %Parametros de filtro digital
        num den xkm1q xkm2q ykm1q ykm2q... %numerador y denominador del filtro digital 
        xkm10 xkm20 ykm10 ykm20
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
    
    %%%%%%%%% PLL %%%%%%%%%%%
    %SE CONVIERTEN AL PLANO DQ
    Vd = sqrt(2/3)*(cos(Theta)*vas_med + cos(Theta-2*pi/3)*vbs_med + cos(Theta+2*pi/3)*vcs_med);
    Vq = sqrt(2/3)*(-sin(Theta)*vas_med - sin(Theta-2*pi/3)*vbs_med - sin(Theta+2*pi/3)*vcs_med);
    v_q_k = Vq;
    
    %PID del PLL
    ylf_k = ylfkm1+ B0*v_q_k + B1*v_q_km1;
    
    %update output frequency
    fo=fn+ylf_k;
    Theta = Theta + 2*pi*(fo*Tm);
    if( Theta >= (2*pi - 2*pi*(fo*Tm)) )
        Theta=0;
    end
    %actualización de valores para uso futuro
    v_q_km1 = v_q_k;
    ylfkm1 = ylf_k;
   
    %%%%%%%%% GENERADOR DE REFERENCIA/S %%%%%%%%%
    %SE CONVIERTEN AL PLANO DQ
    Id = sqrt(2/3)*(cos(Theta)*ial_med + cos(Theta-2*pi/3)*ibl_med + cos(Theta+2*pi/3)*icl_med);
    Iq = sqrt(2/3)*(-sin(Theta)*ial_med - sin(Theta-2*pi/3)*ibl_med - sin(Theta+2*pi/3)*icl_med);
    I0 = sqrt(1/3)*(ial_med + ibl_med + icl_med);

    %SE FILTRA LA POTENCIA ACTVIA Y COMPENSA LA CARGA DEL CAPACITOR:
    %Instante actual
    tact_fd = tact;
    %señal a filtrar
    xkd =  Id;
    xkq =  Iq;
    xk0 = I0;
    if (tact_fd-tant_fd) >= Tm_fd
        ykd = ( num(1)*xkd + num(2)*xkm1d + num(3)*xkm2d - den(2)*ykm1d - den(3)*ykm2d )/den(1);
        tant_fd = tact_fd;
        xkm2d = xkm1d;
        xkm1d = xkd;
        ykm2d = ykm1d;
        ykm1d = ykd;
        
        ykq = ( num(1)*xkq + num(2)*xkm1q + num(3)*xkm2q - den(2)*ykm1q - den(3)*ykm2q )/den(1);
        xkm2q = xkm1q;
        xkm1q = xkq;
        ykm2q = ykm1q;
        ykm1q = ykq;
        
        yk0 = ( num(1)*xk0 + num(2)*xkm10 + num(3)*xkm20 - den(2)*ykm10 - den(3)*ykm20 )/den(1);
        xkm2q = xkm10;
        xkm1q = xk0;
        ykm2q = ykm10;
        ykm1q = yk0;
        
    else
        ykd = ykm1d;
        ykq = ykm1q;
        yk0 = ykm10;
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
    Idc = Id - ykd - pid;
    Iqc = Iq-ykq;
    I0c = I0-yk0;
  
    %SE CONVIERTEN LAS CORRIENTES DE REFERENCIA DEL APF DQ A SU EQUI EN ABC
    ica_ref=  sqrt(2/3)*(sin(Theta)*Idc + cos(Theta)*Iqc + 1*I0c );
    icb_ref=  sqrt(2/3)*(sin(Theta-2*pi/3)*Idc + cos(Theta-2*pi/3)*Iqc +1*I0c);
    icc_ref=  sqrt(2/3)*(sin(Theta+2*pi/3)*Idc + cos(Theta+2*pi/3)*Iqc +1*I0c);
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



