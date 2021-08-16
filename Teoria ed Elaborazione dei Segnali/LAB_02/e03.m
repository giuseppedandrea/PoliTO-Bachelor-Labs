clc
clear

% Variabili
T0 = 4;
fc= 20;
Tc = 1 / fc;
N = T0 * fc;
Df = 1 / T0;

% Segnali "continui"
t = (0:0.01:N - 1);
x1_t = sinc(t * Tc) .^ 2;
x2_t = exp(-4 * abs(t * Tc));
x3_t = cos(2 * pi * t * Tc);

% Segnali campionati a fc
n = (0:N - 1);
x1_n = sinc(n * Tc) .^ 2;
x2_n = exp(-4 * abs(n * Tc));
x3_n = cos(2 * pi * n * Tc);

figure
hold on
stem(n, x1_n, 'r')
stem(n, x2_n, 'g')
stem(n, x3_n, 'b')
plot(t, x1_t, 'r:')
plot(t, x2_t, 'g:')
plot(t, x3_t, 'b:')
xlabel('n')
ylabel('x[n]')
grid on
legend('x1[n]=sinc^2(nTc)', 'x2[n]=e^{-4|nTc|}', 'x3[n]=cos(2\pinTc)')
title('Segnali campionati a fc')

% DFT dei segnali campionati a fc
f = (-N / 2:N/2 - 1) .* Df;
X1_n = fftshift(fft(x1_n, N));
X2_n = fftshift(fft(x2_n, N));
X3_n = fftshift(fft(x3_n, N));

figure
hold on
stem(f, abs(X1_n) .* Tc, 'r')
stem(f, abs(X2_n) .* Tc, 'g')
stem(f, abs(X3_n) .* Tc, 'b')
xlabel('f\cdotf_c')
ylabel('|X(e^{j2\pif})|')
grid on
legend('DTF[sinc^2(nTc)]', 'DTF[e^{-4|nTc|}]', 'DTF[cos(2\pinTc)]')
title('DTF dei segnali campionati a fc')
