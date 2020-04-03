function [vdq] = PLL(x)
global tant Tm fn fo Fm Theta Theta_km1 v_q_km1 ylfkm1 ylf_k Vq Vd B0 B1

tact = x(1);
vas_med =  x(2);
vbs_med =  x(3);
vcs_med =  x(4);
if( (tact-tant) >= Tm )
    
    %SE CONVIERTEN AL PLANO DQ
    Vd = sqrt(2/3)*(cos(Theta)*vas_med + cos(Theta-2*pi/3)*vbs_med + cos(Theta+2*pi/3)*vcs_med);
    Vq = sqrt(2/3)*(-sin(Theta)*vas_med - sin(Theta-2*pi/3)*vbs_med - sin(Theta+2*pi/3)*vcs_med);
    v_q_k = Vq;
    
    %Loop Filter
    ylf_k = ylfkm1+ B0*v_q_k + B1*v_q_km1;
    
    %update output frequency
    fo=fn+ylf_k;
    Theta = Theta + 2*pi*(fo*Tm);
    if( Theta >= (2*pi - 2*pi*(fo*Tm)) )
        Theta=0;
    end
    %update u_q for future use
    v_q_km1 = v_q_k;
    ylfkm1 = ylf_k;
    tant = tact;
    [theta] = Theta;
    [vdq] = [Vd,Vq]
    
else
    %[theta] = Theta;
    [vdq] = [Vd,Vq]
end
end

