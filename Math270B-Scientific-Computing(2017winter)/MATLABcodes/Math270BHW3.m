function Math270BHW3
clear all;
clc;
fprintf('>>>>>>>>>>>>>>>>>>>>>>>> Math 270B Homework 3 Test Program Starts. >>>>>>>>>>>>>>>>>>>>>>>>\n');
TOL = 1e-4;
fprintf('Tolerence = %e set; it will be used in QR algorithm and testing the residuals. \n', TOL);

%% Define the test matrices
A1 = reshape(1:16,4,4)';
fprintf('First test matrix defined: A1 = \n');
disp(A1);

n = 4;
B1 = zeros(n);
B1(1,1) = 4; B1(1,2) = -1;
for i=2:n-1
    B1(i,i-1:i+1) = [-1, 4, -1];
end
B1(n,n-1) = -1; B1(n,n) = 4;
B2 = -eye(n);
A3 = zeros(n*n);
A3(1:n,1:n) = B1; A3(1:n,(1:n)+n) = B2;
for i=2:n-1
    A3((1:n)+(i-1)*n,(1:3*n)+(i-2)*n) = [B2, B1, B2];
end
A3((1:n)+(n-1)*n,(1:n)+(n-2)*n) = B2;
A3((1:n)+(n-1)*n,(1:n)+(n-1)*n) = B1;
fprintf('Third test matrix defined: A3 = \n');
disp(A3);

%% SVD
[U1,S1,V1] = my_svd(A1,TOL);
assert(norm(U1*S1*V1'-A1,1)<TOL, 'FAILED: SVD for 1st test matrix');
assert(norm(U1'*U1-eye(size(U1,2)),1)<sqrt(TOL), 'FAILED: SVD for 1st test matrix');
assert(norm(V1'*V1-eye(size(V1,2)),1)<sqrt(TOL), 'FAILED: SVD for 1st test matrix');
fprintf('TEST PASSED: SVD decomposition for 1st test matrix. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('L1-Norm of Residual (U*S*V\''-A1) = %e\n', norm(U1*S1*V1'-A1,1));
fprintf('L1-Norm of Residual (U\''*U-I)    = %e  (U is orthogonal indeed.) \n', norm(U1'*U1-eye(size(U1,2)),1));
fprintf('L1-Norm of Residual (V\''*V-I)    = %e  (V is orthogonal indeed.) \n', norm(V1'*V1-eye(size(V1,2)),1));
fprintf('U = \n');
disp(U1);
fprintf('S = \n');
disp(S1);
fprintf('V = \n');
disp(V1);

%% Divide & Conquer
% I skipped it. 

%% Lanczos
for k=3*(1:5)
    [Q,T] = my_lanczos(A3,rand(n^2,1),k,TOL);
    assert(norm(A3*Q(:,1:k) - Q*T,1)<TOL, 'FAILED: Lanczos for 3rd test matrix');
    fprintf('L1-Norm of Residual (A3*Qk - Qkp1*T)    = %e\n', norm(A3*Q(:,1:k) - Q*T,1));
    fprintf('The eigenvalues of A3 are :');
    disp(eig(A3)');
    fprintf('The eigenvalues of Tk are :');
    disp(eig(T(1:k,1:k))');
end

fprintf('>>>>>>>>>>>>>>>>>>>>>>>>             All tests passed.             >>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('>>>>>>>>>>>>>>>>>>>>>>>>  Math 270B Homework 3 Test Program Ends.  >>>>>>>>>>>>>>>>>>>>>>>>\n');
end
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
function [Q,T] = my_qr_alg(A,TOL,iter_max)
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
function [c,s] = my_givens(a,b)
if b==0
    c = 1;
    s = 0;
else
    if abs(b) > abs(a)
        t = -a/b;
        s = 1/sqrt(1+t^2);
        c = s*t;
    else
        t = -b/a;
        c = 1/sqrt(1+t^2);
        s = c*t;
    end
end
end
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
