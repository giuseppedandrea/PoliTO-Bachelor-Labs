%% Esercizio 1.3
% Giulio Franzese
% giulio.franzese@polito.it
% 7/12/2018
clc
clear
close all


ntot=10^4;   % Numero totale di campioni
N=10^3;    % Numero di campioni diversi da zero

x=zeros(1,ntot); %%% preallocazione segnale nullo

configBit=0; %0/1 1 per la prima parte dell'esercizio, 0 per la seconda
if(configBit)
    x(1:N)=ones(1,N);
else
    seed=1;
    rng(seed);
    Nup=4;
    x=[filter(ones(1,Nup),1,upsample(sign(randn(1,N/Nup)),Nup)),zeros(1,ntot-N)];
end

Px=sum(x(1:N).^2)/N; % potenza del segnale x
x=x/sqrt(Px); % normalizzazione di potenza (ora x ha potenza unitaria)

D=4000;  % Ritardo in numero di campioni
sigma=5;

[r,noiseless_r]=mychannel(x,D,sigma);


z=xcorr(r,x); % Correlazione tra segnale trasmesso e segnale ricevuto
[Max_value,arg_max]=max(abs(z)); % trovo picco massimo cross correlazione
true_arg_max=arg_max-ntot;
figure
plot(r),hold on,plot(noiseless_r)
legend('segnale ricevuto','segnale ricevuto senza rumore')
xlabel('n')
figure
set(gca,'FontSize',14)
stem([0:ntot-1],z(ntot:end),'b.'),hold on,
legend('cross correlazione calcolata')
stem(true_arg_max,Max_value,'r o')
xlabel('n')
str=strcat('z(n), valore vero ritardo=',num2str(D),' valore stimato=',num2str(true_arg_max));
title(str)
grid on

function [r,noiseless_r]=mychannel(x,D,sigma)
    noiseless_r = [zeros(1, D-1), x(1:end-D+1)];
    noise = sqrt(sigma) * randn(1, length(x));
    r = noiseless_r + noise;
end
