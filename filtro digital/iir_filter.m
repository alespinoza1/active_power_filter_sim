function [yk] = iir_filter(x)
global  Tm_fd fm_fd Ts Tsim tant_fd xkm1 xkm2 ykm1 ykm2... %Parametros de simulacion
        num den %numerador y denominador del filtro digital 
        
%% %%%%%%% SEÑALES DE ENTRADA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Instante actual
tact_fd = x(1);
%señal a filtrar
xk = x(2);

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

end

