function [U,S,V] = my_svd(A,TOL)
% [U,S,V] = my_svd(A)
% the results satisfy A==U*S*V'
if nargin==1
    TOL = 1e-8;
end
[m,~] = size(A);
[Q,D] = my_qr_alg(A'*A,TOL);    %A'A==V*D*V'
[D,I] = sort(diag(D),'descend');
Q = Q(:,I);
p = sum(abs(D)>TOL);
V = Q(:,1:p);
S = diag(sqrt(D(1:p)));
U = zeros(m,p);
for j=1:p
    U(:,j) = A*V(:,j)/S(j,j);
end
end