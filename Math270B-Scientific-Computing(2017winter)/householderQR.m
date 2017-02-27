function Math270BHW1

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
[Q, R] = householderQR(A);
resQR = A - Q*R;
fprintf('Residual of the Householder QR = %f', norm(resQR(:)));

end

function [Q, R] = householderQR(A)
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

