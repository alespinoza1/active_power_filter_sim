% /************************************************************************
%  File name   :	Figuras.m
%  Originator  : 	L. Comparatore
%  Description : 	Figuras, resultados de simulación
%
% -------------------------------------------------------------------------
% =======================================================================*/

clc
%EJECUTAR PRIMERO EL ARCHIVO "GlobalParam.m"
%LUEGO CORRER LA SIMULACION DEL MODELO SIMULINK



%% %%%%%%% DEFINICION DE VARIABLES AUXILIARES %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%para el switching pattern
const=4;
tinicio= 0.044;

fuente= 10;

%%% Custom RGB colour vectors
colour_teal = [18 150 155] ./ 255;
colour_lightgreen = [94 250 81] ./ 255;
colour_green = [12 195 82] ./ 255;
colour_lightblue = [8 180 238] ./ 255;
colour_darkblue = [1 17 181] ./ 255;
colour_yellow = [251 250 48] ./ 255;
colour_peach = [251 111 66] ./ 255;


%% %%%%%%% FIGURAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Corrientes Fase "a"
%figure(1)
%plot(Isa_k,'r')
%hold on
%plot(ILa_k,'b')
%hold on
%plot(Ica_k,'k')
%hold off
%str = sprintf('Titulo');
%titulo1 = title(str);
%set(titulo1, 'FontName', 'Batang', 'fontsize', 10);
%xlim([0 Tsim]);
%ylim([-13 13]);
%xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', 10);
%ylabel('Corriente [A]', 'FontName','Times New Roman', 'fontsize', 10);
%leyenda = legend('i_{s}^{a}','i_{L}^{a}','i_{c}^{a}');
%set(leyenda, 'FontName','Times New Roman', 'fontsize', 10);
%grid on


%Seguimiento de corriente fase "a"
figure(2)
plot(Ica_k,'b')
hold on
plot(ica_ref_k,'r')
hold off
xlim([0 Tsim]);
ylim([-10 10]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Corriente [A]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('{i_{c}^{a}}^{*}','i_{c}^{a}');
set(leyenda, 'FontName', 'Times New Roman', 'fontsize', fuente);
%grid on

%Seguimiento de corriente fase "a" ZOOM
figure(3)
%subplot(2,2,1)
plot(Ica_k,'b')
hold on
plot(ica_ref_k,'r')
hold off
xlim([0.03 0.07]);
ylim([-10 10]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Corriente [A]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('{i_{c}^{a}}^{*}','i_{c}^{a}');
set(leyenda, 'FontName', 'Times New Roman', 'fontsize', fuente);
%grid on


%Potencia activa
figure(4)
plot(Ps_k,'r')
hold on
plot(PL_k,'b')
hold on
plot(Pc_k,'k')
hold off
xlim([0 Tsim]);
ylim([-3000 6000]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Potencia activa [W]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('P_{s}','P_{L}','P_{c}');
set(leyenda, 'FontName','Times New Roman', 'fontsize', fuente);
%grid on

%Potencia reactiva
figure(5)
plot(Qs_k,'r')
hold on
plot(QL_k,'b')
hold on
plot(Qc_k,'k')
hold off
xlim([0 Tsim]);
ylim([-6000 3200]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Potencia reactiva [VAR]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('Q_{s}','Q_{L}','Q_{c}');
set(leyenda, 'FontName','Times New Roman', 'fontsize', fuente);
%grid on

%Potencia reactiva ZOOM
figure(6)
plot(Qs_k,'r')
hold on
plot(QL_k,'b')
hold on
plot(Qc_k,'k')
hold off
xlim([tinicio+const*Tm tinicio+(const+2)*Tm]);
ylim([-6000 3200]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Potencia reactiva [VAR]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('Q_{s}','Q_{L}','Q_{c}');
set(leyenda, 'FontName','Times New Roman', 'fontsize', fuente);
%grid on

%tension de salida del CHB fase "a"
figure(7)
plot(vca_k,'b')
xlim([0 Tsim]);
ylim([-400 400]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Tensión [V]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('v_{c}^{a}');
set(leyenda, 'FontName','Times New Roman', 'fontsize', fuente);
%grid on


%tension de salida del CHB fase "a" ZOOM
figure(8)
plot(vca_k,'b')
%const=0;
xlim([tinicio+const*Tm tinicio+(const+2)*Tm]);
ylim([-400 400]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Tensión [V]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('v_{c}^{a}');
set(leyenda, 'FontName','Times New Roman', 'fontsize', fuente);
%grid on



%tensiones en los capacitores fase "a"
figure(9)
plot(Vcca1_k,'r')
hold on
plot(Vcca2_k,'b')
hold on
plot(Vcca3_k,'g')
hold off
xlim([0 Tsim]);
ylim([80 150]);
xlabel('Tiempo [s]', 'FontName','Times New Roman', 'fontsize', fuente);
ylabel('Tensión [V]', 'FontName','Times New Roman', 'fontsize', fuente);
leyenda = legend('Vcca1_k','Vcca2_k','Vcca3_k');
set(leyenda, 'FontName','Times New Roman', 'fontsize', fuente);
%grid on


%Voltaje y corriente de la fuente fase "a"
%figure(10)
%vx = 0:(Tm/40):0.1;
%[v,v1,v2] = plotyy(vx,Vsa_k.Data,vx,Isa_k.data);
%[v,v1,v2] = plotyy(Vsa_k.Time,Vsa_k.Data,Isa_k.Time,Isa_k.data);
%xlabel('Tiempo [s]','Fontname', 'Batang', 'fontsize', 10);
%axes(v(1)) %eje de la izquierda
%ylim([-400 400]);
%ylabel('Tensión [V]','Color','black',  'Fontname', 'Batang', 'fontsize', fuente);
%axes(v(2)) %eje de la derecha
%ylim([-10 10]);
%ylabel('Corriente [A]','Color','black',  'Fontname', 'Batang', 'fontsize', fuente);
%set(v(1),'ycolor','k') %eje de tension
%set(v(2),'ycolor','k') %eje de corriente
%set(v1,'Color','b'); %gráfica 1
%set(v2,'Color','r'); %gráfica 2
%xlim([0 Tsim]);
%xlabel('Tiempo [s]', 'Fontname', 'Times');
%ylabel('Tensión [V], Current [A]', 'Fontname', 'Times');
%leyenda =legend('V_{s}^{a}','i_{s}^{a}');
%set(leyenda, 'Color','white', 'Fontname', 'Batang', 'fontsize', fuente);
%grid on