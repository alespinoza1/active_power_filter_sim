clear all;
close all;
clc;
Fs = 20000;
Ts = 1/Fs;
Tfinal = 0.1;
t = 0:Ts:Tfinal;
GridFreq = 50;
fn = GridFreq;
wu = 2*pi*GridFreq;
theta = rem( (2*pi*GridFreq*t),2*pi );
L = length(t);

Vs = 220*sqrt(2);
tset = 	20e-3; %30ms tiempo de establecimiento
zeta = 0.707; %factor de amortiguamiento
delta = 0.05;% banda error 5%
wn = -(1/(tset*zeta))*log(delta/(1/sqrt(1-zeta^2)))
kipll = wn^2/Vs
kppll = 2*zeta*wn/Vs
B0 = (2*kppll+kipll*Ts)/2
B1 = -(2*kppll-kipll*Ts)/2

%Caso 1:
for n = 1:floor(L/2)
    Ua(n) = Vs*cos( theta(n) );
    Ub(n) = Vs*cos( theta(n)-2*pi/3 );
    Uc(n) = Vs*cos( theta(n)-4*pi/3 );
end
for n = floor(L/2):L
    Ua(n) = Vs*cos( theta(n) + 1.5);
    Ub(n) = Vs*cos( theta(n)-2*pi/3 + 1.5 );
    Uc(n) = Vs*cos( theta(n)-4*pi/3 + 1.5 );
end

%CASE 2: Unbalanced Grid
% for n=1:floor(L)
% Ua(n)=cos(theta(n));
% Ub(n)=1.1*cos(theta(n)-2*pi/3);
% Uc(n)=cos(theta(n)-4*pi/3);
% end
% Ua_ideal=cos(theta);
%CASE 3: voltage harmonics
% for n=1:floor(L)
% Ua(n)=cos(theta(n))+0.05*cos(5*theta(n));
% Ub(n)=cos(theta(n)-2*pi/3)+0.05*(cos(5*(theta(n)-2*pi/3)));
% Uc(n)=cos(theta(n)-4*pi/3)+0.05*(cos(5*(theta(n)-4*pi/3)));
% end
% Ua_ideal=cos(theta);
% CASE 4: voltage dips and swells
%for n=1:floor(L/2)
%Ua(n)=cos(theta(n));
%Ub(n)=cos(theta(n)-2*pi/3);
%Uc(n)=cos(theta(n)-4*pi/3);
%end
%for n=floor(L/2):L
%Ua(n)=0.7*cos(theta(n));
%Ub(n)=0.7*cos(theta(n)-2*pi/3);
%Uc(n)=0.7*cos(theta(n)-4*pi/3);
%end
Ua_ideal = Ua;
ylf = [0,0];
u_q = [0,0];
Theta = [0,0,0];
fo = 0;
Ualpha = [0,0];
Ubeta = [0,0];
Ud_plus = [0,0];
Uq_plus = [0,0];
fn = 0;
wo = 0;
%simulando el pll 
for n = 3:L
    Ualpha(n) = (2/3)*( Ua(n)-0.5*( Ub(n)+Uc(n) ) );
    Ubeta(n) = (2/3)*0.866*(Ub(n)-Uc(n));
    Ud_plus(n) = Ualpha(n)*cos(Theta(n)) + Ubeta(n)*sin(Theta(n));
    Uq_plus(n) = -Ualpha(n)*sin(Theta(n)) + Ubeta(n)*cos(Theta(n));
    u_q(1) = Uq_plus(n);
    
    ylf(1) = ylf(2) + B0*u_q(1) + B1*u_q(2);
    
    u_q(2) = u_q(1);
    ylf(2) = ylf(1);
    
    fo = fn + ylf(1);
    Theta(n+1) = Theta(n) + 2*pi*fo*Ts;
    if( Theta(n+1) >= ( 2*pi-2*pi*fo*Ts ) )
        Theta(n+1) = 0;
    end
end
figure(1)
plot(t,Ua_ideal,'r','LineWidth',2)
hold on 
plot(t,Vs*cos(Theta(1:L)),'b','LineWidth',0.5)
xlim([0 0.1]);
ylim([-320 320]);
xlabel('Tiempo [s]','Interpreter','latex','fontsize', 18);
ylabel('Voltaje [A]','Interpreter','latex', 'fontsize', 18);
leyenda = legend('${V_{s}^{a}}$','$V_{pll}^{a}$');
set(leyenda,'Interpreter','latex', 'fontsize', 18);
set(gca, 'FontSize', 18)
grid on 

figure(2)
plot(t,Theta(1:L).*180/pi,'b','LineWidth',2)
hold on 
xlim([0 0.1]);
ylim([-0.1 360]);
xlabel('Tiempo [s]','Interpreter','latex','fontsize', 18);
ylabel("Angulo de fase [grados]",'Interpreter','latex', 'fontsize', 18);
leyenda = legend('$ \theta_{pll}$');
set(leyenda,'Interpreter','latex', 'fontsize', 18);
set(gca, 'FontSize', 18)
grid on


figure(3)
plot(t,Ud_plus(1:L),'r','LineWidth',2)
hold on 
plot(t,Uq_plus(1:L),'b','LineWidth',2)
xlabel('Tiempo [s]','Interpreter','latex','fontsize', 18);
ylabel('Voltaje en $DQ$','Interpreter','latex', 'fontsize', 18);
leyenda = legend('$ V_{d}$','$ V_{q}$');
set(leyenda,'Interpreter','latex', 'fontsize', 18)
set(gca, 'FontSize', 18)
grid on 




    


