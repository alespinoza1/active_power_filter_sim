% /************************************************************************
%  File name   :	angulos.m
%  Originator  : 	L. Comparatore
%  Description : 	Resolucion del sistema de ecuaciones para el calculo de
%  los angulos posteriormente utilizados en la modulacion Staircase
%  Date        : 
% -------------------------------------------------------------------------
% =======================================================================*/
function [salida] = angulos( ma1 )
%recibe como argumento el indice de modulacion y devuelve los 3 angulos

step = 1e-3;
ang1 = 0:step:pi/2;
ang2 = 0:step:pi/2;
ang3 = 0:step:pi/2;

epsilon = length(ang1);
e = 0.1; % error de precision

for i=1:epsilon
    for j=1:epsilon
        for k=1:epsilon
            
            %ecuacion 1
            a1 = cos(ang1(i));
            b1 = cos(ang2(j));
            c1 = cos(ang3(k));
            %ecuacion 2
            a2 = cos(5*ang1(i));
            b2 = cos(5*ang2(j));
            c2 = cos(5*ang3(k));
            %ecuacion 3
            a3 = cos(7*ang1(i));
            b3 = cos(7*ang2(j));
            c3 = cos(7*ang3(k));
            
            if (a1+b1+c1 <= 3* ma1+e) && (a1+b1+c1 >= 3* ma1-e)   &&   (a2+b2+c2 <= 0+e) && (a2+b2+c2 >= 0-e)   &&   (a3+b3+c3 <= 0+e) && (a3+b3+c3 >= 0-e)  
                x=ang1(i);
                y=ang1(j);
                z=ang1(k); 
            end
        end
    end
end

%salida
salida = [x y z];





