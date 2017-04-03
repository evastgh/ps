function [Q,U] = my_householder(A)
% [Q,U] = my_householder(A)
% the results give Q*A==U where U is upper Hessenberg
[m, n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;

if n < 3
    Q = eye(n);
    U = A;
    return
end

Q = eye(n);
U = A;
for m = 1:n-2
    u = A(m+1:end, m);
    alpha = -sign(u(1))*norm(u);
    r = sqrt(0.5*alpha*(alpha-u(1)));
    v = [0; (0.5/r)*u];
    v(2) = v(2) - 0.5*alpha/r;
    P = eye(n-m+1) - 2* v* (v');
    Q = [eye(m), zeros(m, n-m); zeros(n-m, m), P(2:end, 2:end)]*Q;
    U(m:end, m:end) = P*A(m:end,m:end);
end
end
