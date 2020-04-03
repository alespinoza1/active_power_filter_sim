function [IRDabc] = DQGEN(x)
%% PARAMETROS DEL PLL DIGITAL %%
global Tm fo fn Theta v_q_km1 ylfkm1 B0 B1 ica_ref icb_ref icc_ref Vdc

global  Tm_fd fm_fd tant_fd xkm1d xkm2d ykm1d ykm2d...%Parametros de filtro digital
        num den xkm1q xkm2q ykm1q ykm2q... %numerador y denominador del filtro digital 
        xkm10 xkm20 ykm10 ykm20
%% PARAMETROS DEL PID CONTROL %%    
global Tmpi kp ki tantpi  err_antpi resp_ant  tantg 
%%%%%%%%% SEÑALES DE ENTRADA %%%%%%%%
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
% tension medida en el capacitor de la celda puente H
vcca = x(8)
%Se espera el tiempo de muestreo
if tact-tantg >= Tm
    
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
    I0c = I0;
  
    %SE CONVIERTEN LAS CORRIENTES DE REFERENCIA DEL APF DQ A SU EQUI EN ABC
    ica_ref=  sqrt(2/3)*(sin(Theta)*Idc + cos(Theta)*Iqc + 1*I0c );
    icb_ref=  sqrt(2/3)*(sin(Theta-2*pi/3)*Idc + cos(Theta-2*pi/3)*Iqc +1*I0c);
    icc_ref=  sqrt(2/3)*(sin(Theta+2*pi/3)*Idc + cos(Theta+2*pi/3)*Iqc +1*I0c);
    
    tantg = tact;
    
    IRDabc=[ica_ref, icb_ref, icc_ref];
    
else
    IRDabc=[ica_ref, icb_ref, icc_ref];
end

