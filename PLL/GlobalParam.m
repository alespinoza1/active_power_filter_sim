clc
clear all
close all

global tant Tm fn fo Fm Theta Theta_km1 v_q_km1 ylfkm1 ylf_k Vq Vd B0 B1 Vs

Fm = 20000;
Tm = 1/Fm;
fn = 50; %Hz
tant = 0;
Theta = 0;
v_q_km1 = 0;
ylfkm1 = 0;
Theta = 0;
Theta_km1 = 0;
ylf_k =0;
Vd = 0;
Vq = 0;
Vs = 120*sqrt(2);
tset = 	20e-3; %30ms tiempo de establecimiento
zeta = 0.707; %factor de amortiguamiento
delta = 0.05;% banda error 5%
wn = -(1/(tset*zeta))*log(delta/(1/sqrt(1-zeta^2)))
kipll = wn^2/Vs
kppll = 2*zeta*wn/Vs
B0 = (2*kppll+kipll*Tm)/2
B1 = -(2*kppll-kipll*Tm)/2



