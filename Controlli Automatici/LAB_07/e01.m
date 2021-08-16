clear all
close all

s=tf('s');

F=(13.5*(s+4)*(s+10))/(s+3)^3
Kf=dcgain(F)

Kr=1;

Kc=1/(0.01*Kf)

Ga1=(Kc/s)*F/Kr;

wb=6;
wcd=0.63*wb
wcd=3.8;

bode(Ga1)
[m1, f1]=bode(Ga1, wcd)

% 2 reti anticipatrici con md=4
md=4;
xd=1;
taud=xd/wcd;
Rd=(1+taud*s)/(1+taud*s/md);
Ga2=Ga1*Rd^2;
[m2, f2]=bode(Ga2, wcd)

% 1 rete attenuatrice con mi=17.4
mi=17.4
figure, bode((1+s/mi)/(1+s))
xi=200;
taui=xi/wcd;
Ri=(1+taui*s/mi)/(1+taui*s);
Ga3=Ga2*Ri;
[m3, f3]=bode(Ga3, wcd)

figure, margin(Ga3)

C=Kc/s*Rd^2*Ri;

W=feedback(C*F, 1/Kr);
figure, bode(W)
figure, margin(W)