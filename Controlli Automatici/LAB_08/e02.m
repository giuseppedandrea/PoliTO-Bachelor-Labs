clear all
close all

s=tf('s');

F=(5*(1+s/4))/((1+s)^2*(1+s/16)^2);
damp(F)
step(F)

Kf=5;
thetaf=0.22;
tauf=2-thetaf;
Fapprox=(Kf*exp(-thetaf*s))/(1+tauf*s)
figure, step(F, Fapprox)

Kp=(1.2*tauf)/(Kf*thetaf);
Ti=2*thetaf;
Td=0.5*thetaf;
N=10;

PID=Kp*(1+1/(Ti*s)+(Td*s)/(1+Td*s/N))

W=feedback(PID*F, 1);
figure, margin(W)
figure, step(W)