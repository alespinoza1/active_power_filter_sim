function [resp] = pi_control(x)

global Tmpi kp ki tantpi  err_antpi resp_ant

tact = x(1);
referencia = x(2);
salida_med = x(3);

if (tact - tantpi) >= Tmpi
    err_act = referencia - salida_med;
    resp = resp_ant + kp*(err_act - err_antpi) + Tmpi*ki*err_act;
    resp_ant = resp;
    err_antpi = err_act;
    tantpi = tact;
else
    resp = resp_ant;
end
end

