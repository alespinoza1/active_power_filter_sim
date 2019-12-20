% /************************************************************************
%  File name   :	VSD.m
%  Originator  : 	L. Comparatore
%  Description : 	Diagrama Vector Space Decomposition (VSD) para el CHB
%                   trifasico de 3 niveles
%
% -------------------------------------------------------------------------
% =======================================================================*/

clc
%clear all

%% %%%%%%% CONSTANTES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%K=1/3; %amplitud invariante
%K=2/3; %amplitud invariante
%K= sqrt(2/3); %potencia invariante
%K=1;

%e = 2.718281828459045235360; %numero de Euler o constante de Napier

%Vector tension (en el plano alfa-beta)
V = [];
xv = [];
yv = [];
mv= [];
pha=[];
matriz=[];

ind=1;


for inda=1:c
    for indb=1:c
        for indc=1:c
            %tension de salida del CHB por fase
            %va =Vc(1,inda);
            %vb =Vc(1,indb);
            %vc =Vc(1,indc);
            va =Vc(1,inda)*Vdc;
            vb =Vc(1,indb)*Vdc;
            vc =Vc(1,indc)*Vdc;
            % tensiones linea a linea
            vAB = va -vb;  
            vBC = vb -vc;
            vCA = vc -va;
            %vector tension
            V(1,ind)= fixdec( K*(vAB + vBC*e^(2/3*pi*1i) + vCA*e^(4/3*pi*1i)), 4);
            %V(1,ind)= K*(vAB + vBC*e^(2/3*pi*1i) + vCA*e^(4/3*pi*1i));
            %parte real
            xv(1,ind)= real(V(1,ind));
            %parte imaginaria
            yv(1,ind)= imag(V(1,ind));
            %modulo
            mv(1,ind)= abs(V(1,ind));
            %fase
            pha(1,ind) = angle(V(1,ind))*180/pi;
            %matriz inda indb indc mv fase
            matriz(ind,:)=[inda indb indc mv(1,ind) pha(1,ind)];
            
            ind= ind +1;
        end
    end
end     

%cantidad total de vectores
vl= length(V);
fprintf('cantidad total de vectores: %d\n', vl)



%Diagram VSD
figure(1)
plot(V, 'b+')


%figure(2)
%axis([min(xv) max(xv) min(xv) max(yv)])
%for ind=1:vl
%    plot(xv(1,ind), yv(1,ind), 'b+')
%    hold on
%    %pause
%end






