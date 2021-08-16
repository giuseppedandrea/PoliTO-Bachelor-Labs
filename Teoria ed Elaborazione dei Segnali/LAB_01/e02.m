clc
clear

N = 10 ;

% Utilizzando la funzione cconv
nn = 0:4;
xx = sin(pi * nn / 5);
yy = ones(1, 3);
zz = cconv(xx, yy, N);
zzz = conv(xx, yy);

%Utilizzando la formula di convoluzione circolare
n = 0:4;
x = [sin(pi * n / 5), zeros(1, N-5)];
y = [ones(1, 3), zeros(1, N-3)];
z = zeros(1, N);
for index=0:(N-1)
    y_ = zeros(1, N);
    for p=0:(N-1)
        y_(p+1) = y(mod(index-p,N)+1);
    end
    z(index+1) = sum(x.*y_)
end
