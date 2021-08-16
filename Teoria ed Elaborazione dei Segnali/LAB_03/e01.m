clc
clear

% Variabili
filename = 'sample_bass.flac';
Fs = 44100;
seconds = 1;

N = seconds * Fs; % Numero di campioni
x = audioread(filename, [1, N]); % Segnale audio campionato

figure
plot(1:N, x)
xlabel('n')
ylabel('x(n)')
grid on
title('Segnale audio')

S = (abs(fftshift(fft(x, N)) .^ 2)) ./ N;

f = linspace(-0.5, 0.5, N); % Asse delle frequenze

figure
plot(f, 10 * log10(S))
xlabel('f')
ylabel('S_x(k) [dB]')
grid on
title('Periodogramma semplice')
