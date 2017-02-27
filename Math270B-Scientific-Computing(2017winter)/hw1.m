function hw1
%% build sample matrix A
n = 10;
A = zeros(n);
A(1,1) = 2;
A(1,2) = -1;
for i=2:n-1
    A(i,i-1) = -1;
    A(i,i) = 2;
    A(i,i+1) = -1;
end
A(n,n-1) = -1;
A(n,n) = 2;

%% QR
[Q, R] = myhouseholderQR(A);
resQR = A - Q*R;
format shortEng;
fprintf('Residual of the Householder QR = \n');
disp(norm(resQR(:)));

%% LU
[L,U] = myLU(A);
resLU = A - L*U;
format shortEng;
fprintf('Residual of LU = \n');
disp(norm(resLU(:)));
end

function [Q, R] = myhouseholderQR(A)
% [Q, R] = householderQR(A)
% Computes the QR-decomposition of input matrix A
[m,n] = size(A);
Q = eye(m);
for j=1:n-1
    x = A(j:m, j);
    v = [zeros(j-1, 1); x + norm(x) * eye(m-j+1,1)];
    Pv = eye(m) - (2*v)*v'/(v'*v);
    A = Pv * A;
    Q = Pv * Q;
end
Q = Q';
R = A;
end

function [L, U] = myLU(A)
[m,n] = size(A);
assert(m==n, 'Input is not a square matrix.\n');
clear m;

L = eye(n);
U = A;
for j=1:n-1
    for i=j+1:n
        factor = U(i,j) / U(j,j);
        U(i,:) = U(i,:) - factor * U(j,:);
        L(i,:) = L(i,:) - factor * L(j,:);
    end
end
L = inv(L);
end
