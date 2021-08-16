clear all
close all

s=tf('s');

F=(5*(s+20))/(s*(s^2+2.5*s+2)*(s^2+15*s+100));
Kf=dcgain(s*F)

Kr=2;

Kca=Kr/(Kf*0.05/Kr)
Kcb=1/(0.02/Kr)

Kc=160

ts=1;
wb=3/ts;
wc=0.63*wb
wcd=1.9

s_capello=0.3;
Mr=(1+s_capello)/0.9;
m_lim=60-5*20*log10(Mr)

Ga1=Kc*F/Kr;
figure, bode(Ga1);
[m1, f1]=bode(Ga1, wcd)

% 2 reti anticipatrici da md=6
md=6;
xd=1.3;
taud=xd/wcd;
Rd=(1+taud*s)/(1+taud*s/md);
Ga2=Ga1*Rd^2;
figure, bode(Ga2);
[m2, f2]=bode(Ga2, wcd)

% 1 rete attenuatrice con mi=33.5
mi=21.5;
xi=200;
taui=xi/wcd;
Ri=(1+taui*s/mi)/(1+taui*s);
Ga3=Ga2*Ri;

C=Kc*Rd^2*Ri;
W=feedback(C*F, 1/Kr);
figure, margin(W)
figure, step(W)