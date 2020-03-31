clear all;
close all;
clc;
Fs = 10000;
Ts = 1/Fs;
Tfinal = 0.2;
t = 0:Ts:Tfinal;
GridFreq = 50;
fn = GridFreq;
wu = 2*pi*GridFreq;
theta = rem( (2*pi*GridFreq*t),2*pi );
L = length(t);
%Caso 1:
for n = 1:floor(L/2)
    Ua(n) = cos( theta(n) );
    Ub(n) = cos( theta(n)-2*pi/3 );
    Uc(n) = cos( theta(n)-4*pi/3 );
end
for n = floor(L/2):L
    Ua(n) = cos( theta(n) + 1.5);
    Ub(n) = cos( theta(n)-2*pi/3 + 1.5 );
    Uc(n) = cos( theta(n)-4*pi/3 + 1.5 );
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
fn = fn;
wo = 0;
%simulando el pll 
for n = 3:L
    Ualpha(n) = (2/3)*( Ua(n)-0.5*( Ub(n)+Uc(n) ) );
    Ubeta(n) = (2/3)*0.866*(Ub(n)-Uc(n));
    Ud_plus(n) = Ualpha(n)*cos(Theta(n)) + Ubeta(n)*sin(Theta(n));
    Uq_plus(n) = -Ualpha(n)*sin(Theta(n)) + Ubeta(n)*cos(Theta(n));
    u_q(1) = Uq_plus(n);
    
    ylf(1) = ylf(2) + 167.9877775*u_q(1) - 165.2122225*u_q(2);
    
    u_q(2) = u_q(1);
    ylf(2) = ylf(1);
    
    fo = fn + ylf(1);
    Theta(n+1) = Theta(n) + 2*pi*fo*Ts;
    if( Theta(n+1) >= ( 2*pi-2*pi*fo*Ts ) )
        Theta(n+1) = 0;
    end
end

figure(3)
subplot(3,1,1)
plot(t,Ua,'r',t,Ub,'b',t,Uc,'g')
title('Ua,Ub,Uc')
subplot(3,1,2)
plot(t,Ualpha,'r',t,Ubeta)
title('alpha beta')
subplot(3,1,3)
plot(t,Ud_plus(1:L),t,Uq_plus(1:L))
title('Ud Uq')
figure(4)
subplot(2,1,1)
plot(t,Ua_ideal,'r',t,cos(Theta(1:L)),'b')
title('Input AC ideal and Locked AC');
subplot(2,1,2)
plot(t,Ua_ideal-cos(Theta(1:L)))
title('Error');

    


