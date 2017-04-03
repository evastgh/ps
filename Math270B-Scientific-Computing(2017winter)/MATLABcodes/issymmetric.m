function tf = issymmetric(A,TOL)
if nargin < 2
    TOL = 1e-8;
end
[m,n] = size(A);
assert(m==n, 'Input is not a square matrix. ');
clear m;

for i=1:n
    for j=i+1:n
        if abs(A(i,j)-A(j,i))>TOL
            tf = false;
            return
        end
    end
end
tf = true;
end