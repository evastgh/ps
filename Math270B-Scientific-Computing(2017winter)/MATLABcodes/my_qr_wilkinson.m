function [Z,T] = my_qr_wilkinson(T)
% [Z,T] = my_qr_wilkinson(A)
% T==Z'*A*Z where Z'*(A-m*eye(n)) is upper triangular
% and m is the Wilkinson shift

[m,n] = size(T);
assert(m==n, 'Input is not a square matrix. ');
clear m;
assert(issymmetric(T), 'Input is not symmetric. ');
assert(sum(sum(abs(tril(T,-2))))/(sum(abs(diag(T)))+sum(abs(diag(T,-1))))<1e-4, 'Input is not tridiagonal. ');

Z = eye(n);
d = 0.5*(T(n-1,n-1)-T(n,n));
if d==0
    m = T(n,n)-T(n,n-1)^2/abs(T(n,n-1));
else
    m = T(n,n)-T(n,n-1)^2/(d+sign(d)*sqrt(d^2+T(n,n-1)^2));
end
x = T(1,1) - m;
z = T(2,1);
for k=1:n-1
    [c,s] = my_givens(x,z);
    T([k,k+1],:) = [c,s;-s,c]'*T([k,k+1],:);
    Z(:,[k,k+1]) = Z(:,[k,k+1])*[c,s;-s,c];
    T(:,[k,k+1]) = T(:,[k,k+1])*[c,s;-s,c];
    if k<n-1
        x=T(k+1,k);
        z=T(k+2,k);
    end
end
end