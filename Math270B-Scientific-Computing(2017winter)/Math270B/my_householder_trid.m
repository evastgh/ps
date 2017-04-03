function [Q,T] = my_householder_trid(A)
% [Q,T] = my_householder(A)
% the results give Q'*A*Q==T where T is tridiagonal
[m, n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;
assert(issymmetric(A), 'Input is not symmetric. ');

Q = eye(n);
T = A;

for k=1:n-2
    [v,b] = house(T(k+1:n,k));
    u = [zeros(k,1);v];
    P = eye(n)-(b*u)*u';
    Q = Q*P;
    T = P*T*P;
end
end

function [v, b] = house(x)
m = length(x);
s = x(2:m)'*x(2:m);
v = [1; x(2:m)];
if s==0 && x(1)>=0
    b = 0;
elseif s==0 && x(1)<0
    b = 2;
else
    mu = norm(x);
    if x(1) <= 0
        v(1) = x(1) - mu;
    else
        v(1) = -s / (x(1) + mu);
    end
    b = 2*v(1)^2/(s+v(1)^2);
    v = v/v(1);
end
end

