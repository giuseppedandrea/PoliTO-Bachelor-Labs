clc
clear

n = 0:4;
x = sin(pi * n / 5);
y = ones(3, 1);
Nx = length(x);
Ny = length(y);
Nz = Nx + Ny - 1;
z = zeros(1,Nz);
for i = 1:Nx
      for k = 1:Ny
       z(i+k-1) = z(i+k-1) + y(k)*x(i);
      end
end