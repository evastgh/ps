function [Q,T] = my_qr_alg(A,TOL,iter_max)
% [Q,D] = my_qr_alg(A,TOL,iter_max)
% the results satisfy A==Q*D*Q'
if nargin==1
    TOL = 1e-8;
    iter_max = 2000;
elseif nargin==2
    iter_max = 2000;
end
[m,n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;
assert(issymmetric(A,TOL^2), 'Input is not symmetric. ');

[Q,T] = my_householder_trid(A);
for iter = 1:iter_max
    for i=1:n-1
        if abs(T(i+1,i))<TOL*(T(i,i)+T(i+1,i+1))
            T(i+1,i) = 0;
            T(i,i+1) = 0;
        end
    end
    
    for q=0:n-2
        if abs(T(n-q,n-q-1))>TOL  %==0
            break
        end
        q = n-1;
    end
    for p=n-q-1:-1:1
        if abs(T(p+1,p))<TOL  %==0
            break
        end
        p = 0;
    end
    
    if q == n-1
        return
    end
    [Z,T(p+1:n-q,p+1:n-q)] = my_qr_wilkinson(T(p+1:n-q,p+1:n-q));
    Q(:,p+1:n-q) = Q(:,p+1:n-q)*Z;
end
end