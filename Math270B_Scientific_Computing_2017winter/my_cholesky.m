function L = my_cholesky(A)
% L = my_cholesky(A)
% the result satisfies A==L*L'
[m,n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;
assert(issymmetric(A), 'Input is not symmetric. ');

A(:,1) = A(:,1)/sqrt(A(1,1));
for j=2:n
    A(j:n,j) = A(j:n,j) - A(j:n,1:j-1)*A(j,1:j-1)';
    A(j:n,j) = A(j:n,j)/sqrt(A(j,j));
end
L = tril(A);
end