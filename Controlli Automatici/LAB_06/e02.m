clear all
close all

s=tf('s');
F=(s-1)/((s+0.2)*(s^3+2.5*s^2+4*s));

% a)
Kf=dcgain(s*F)
damp(F)
bode(F)

% b)
Kc=1;
Kr=0.5;
Ga=Kc*F/Kr;

figure, bode(Ga)

% c)
figure, nyquist(Ga)

% d)
Kc=-0.1;
Ga=Kc*F/Kr;
W=feedback(Kc*F, 1/Kr)
damp(W)

% e)
We=Kr*feedback(1, Ga);
Wd1=feedback(F, Kc/Kr);
Wd2=feedback(1, Ga);

% r=t d1=0.1 d2=0.5
e_r=dcgain(s*We*1/s^2);
e_d1=dcgain(s*Wd1*0.1/s);
e_d2=dcgain(s*Wd2*0.5/s);
e_tot=e_r-(e_d1+e_d2)

% r=2 d1=0.1 d2=0.01t
e_r=dcgain(s*We*2/s);
e_d1=dcgain(s*Wd1*0.1/s);
e_d2=dcgain(s*Wd2*0.01/s^2);
e_tot=e_r-(e_d1+e_d2)