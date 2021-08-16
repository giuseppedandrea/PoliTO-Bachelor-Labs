clear all
close all

s=tf('s');
F=(s^2+11*s+10)/(s^4+4*s^3+8*s^2);

% a)
Kf=dcgain(s^2*F)
damp(F)
bode(F)

% b)
Kc=1;
Kr=1;
Ga=Kc*F/Kr;

figure, bode(Ga)

% c)
figure, nyquist(Ga)

% d)
W=feedback(Kc*F, 1/Kr)
damp(W)

% e)
We=feedback(1, Ga);
Wd1=feedback(F, Kc/Kr);
Wd2=feedback(1, Ga);

% r=t d1=0.1 d2=0.5
e_r=dcgain(s*We*1/s^2);
e_d1=dcgain(s*Wd1*0.1/s);
e_d2=dcgain(s*Wd2*0.5/s);
e_tot=e_r-(e_d1+e_d2)

% r=2t d1=0 d2=0.01t
e_r=dcgain(s*We*2/s^2);
e_d1=dcgain(s*Wd1*0/s);
e_d2=dcgain(s*Wd2*0.01/s^2);
e_tot=e_r-(e_d1+e_d2)

% r=t^2/2 d1=0 d2=0
e_r=dcgain(s*We*1/s^3);
e_d1=dcgain(s*Wd1*0/s);
e_d2=dcgain(s*Wd2*0/s);
e_tot=e_r-(e_d1+e_d2)

% r=t^2/2 d1=0.1 d2=0.2
e_r=dcgain(s*We*1/s^3);
e_d1=dcgain(s*Wd1*0.1/s);
e_d2=dcgain(s*Wd2*0.2/s);
e_tot=e_r-(e_d1+e_d2)