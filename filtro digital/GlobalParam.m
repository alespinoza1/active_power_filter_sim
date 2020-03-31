clc
clear all
close all
global  Tm_fd fm_fd Ts Tsim tant_fd xkm1 xkm2 ykm1 ykm2... %Parametros de simulacion
        num den %numerador y denominador del filtro digital 
    fm_fd = 1000;
    fn = fm_fd/2;
    Tm_fd = 1/fm_fd;
    Ts = Tm_fd/10;
    Tsim = 1;
    %[N Wc] = buttord(25/fn, 125/fn, 1, 20); % fc = 25Hz, fs = 125Hz, Gc = -1dB, Gp = -20dB
    [num den] = butter(2,25/fn,'low');
    bode(num,den)
    fvtool(num,den)
    tant_fd = 0;
    xkm1 = 0;
    xkm2 = 0;
    ykm1 = 0;
    ykm2 = 0;
    