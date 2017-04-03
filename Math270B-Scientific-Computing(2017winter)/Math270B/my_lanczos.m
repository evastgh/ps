function [Q,T] = my_lanczos(A,q1,k,TOL)
% [Q,T] = my_lanczos(A,q1,k)
% Q is n-by-(k+1)
% T is (k+1)-by-k
% the results satisfy A*Q(:,1:k) = Q*T
if nargin==3
    TOL = 1e-8;
end
[m,n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;
assert(issymmetric(A,TOL^2), 'Input is not symmetric. ');

Q = zeros(n,k);
a = zeros(k,1);
b = zeros(k,1);

q1 = q1/norm(q1);   %just in case!

Q(:,1) = q1;
a(1) = q1'*A*q1;
r = A*q1-a(1)*q1;
b(1) = norm(r);
q0 = q1;    q1 = r/b(1);
Q(:,2) = q1;
for i=2:k
    a(i) = q1'*A*q1;
    r = A*q1-a(i)*q1-b(i-1)*q0;
    b(i) = norm(r);
    q0 = q1;    q1 = r/b(i);
    Q(:,i+1) = q1;
end
T = [diag(a)+diag(b(1:k-1),1)+diag(b(1:k-1),-1);
    zeros(1,k-1),b(k)];
end
