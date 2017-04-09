function [P,L,U] = my_lu(A)
% [P,L,U] = my_lu(A)
% the result satisfies P*A==L*UU

[m,n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;

p = 1:n;
for k=1:n-1
    [x,m] = max(abs(A(k:n,k)));
    m = m + k - 1;
    temp = p(k); p(k) = p(m); p(m) = temp;   %exchange p(k) and p(m)
    T = A(k,:); A(k,:) = A(m,:); A(m,:) = T; %exchange A(k,:) and A(m,:)
    if x == 0
        fprintf('WARN: Input matrix is singular. LU process terminated. ');
        break
    end
    A(k+1:n,k) = A(k+1:n,k)/A(k,k);
    A(k+1:n,k+1:n) = A(k+1:n,k+1:n) - A(k+1:n,k)*A(k,k+1:n);
end
P = sparse(1:n,p,ones(n,1),n,n,n);
L = eye(n) + tril(A,-1);
U = triu(A);
end