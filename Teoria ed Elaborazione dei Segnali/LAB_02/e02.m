clc
clear

N = 5;
n = 1:N;
x = sin(pi * n / 5);

X = zeros(1, N);
for k = 0:N-1
      for n = 0:N-1
        X(k+1) = X(k+1) + (x(n+1) * exp(-1i * 2 * pi * n * k / N));
      end
end
XX=fft(x);

IX = zeros(1, N);
for n = 0:N-1
      for k = 0:N-1
        IX(n+1) = IX(n+1) + (X(k+1) * exp(1i * 2 * pi * n * k / N)) * (1 / N);
      end
end
IXX=ifft(XX);