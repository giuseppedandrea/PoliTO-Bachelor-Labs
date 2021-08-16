clc
clear

% Variabili
filename = 'sample_bass.flac';
Fs = 44100;
seconds = 1;
M1 = 10;
M2 = 50;
M3 = 100;

N = seconds * Fs; % Numero di campioni
x = audioread(filename, [1, N]); % Segnale audio campionato

figure
plot(1:N, x)
xlabel('n')
ylabel('x(n)')
grid on
title('Segnale audio')

[S1, f1] = periodogrammaWelch(x, M1);
[S2, f2] = periodogrammaWelch(x, M2);
[S3, f3] = periodogrammaWelch(x, M3);

figure
hold on
plot(f1, 10 * log10(S1), 'r')
plot(f2, 10 * log10(S2), 'g')
plot(f3, 10 * log10(S3), 'b')
xlabel('f')
ylabel('S_x(k) [dB]')
grid on
legend('M = 10', 'M = 50', 'M = 100')
title('Periodogramma di Welch')

function [S, f] = periodogrammaWelch(x, M)
    % Ingressi:
    % x -> Segnale campionato
    % M -> Numero di sottosequenze
    % Uscite:
    % S -> Periodogramma
    % f -> Asse delle frequenze
    
    N = length(x); % Numero di campioni del segnale campionato
    Nftt = N / M; % Numero di campioni della FFT da calcolare
    S = zeros(Nftt, 1); % Inizializzazione del periodogramma
    for i = 1:M
        xi = x(((i-1) * Nftt) + 1:i * Nftt) .* hamming(Nftt);
        S = S + (abs(fftshift(fft(xi, Nftt)) .^ 2)) ./ Nftt;
    end
    shift = floor(Nftt / 2);
    for i = 1:(M - 1)
        xi = x(((i-1) * Nftt) + shift + 1:(i * Nftt) + shift) .* hamming(Nftt);
        S = S + (abs(fftshift(fft(xi, Nftt)) .^ 2)) ./ Nftt;
    end
    
    S = (1 / M) .* S; % Periodogramma normalizzato
    f = linspace(-0.5, 0.5, Nftt); % Asse delle frequenze
end