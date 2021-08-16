clc
clear

% Utilizzando la funzione conv
nn = 0:4;
xx = sin(pi * nn / 5);
yy = ones(1, 3);
zz = conv(xx, yy);

%Utilizzando la formula di convoluzione lineare
n = 0:4;
x = [zeros(1, 2), sin(pi * n / 5), zeros(1, 2)];
z = zeros(1, 7);
for index=1:(length(xx)+length(yy)-1)
    y = [zeros(1, index-1), ones(1, 3), zeros(1, length(xx)+length(yy)-1-index)];
    z(index) = sum(x.*y);
end



