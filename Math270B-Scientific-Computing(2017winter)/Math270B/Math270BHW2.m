function Math270BHW2
clear all;
clc;
fprintf('>>>>>>>>>>>>>>>>>>>>>>>> Math 270B Homework 2 Test Program Starts. >>>>>>>>>>>>>>>>>>>>>>>>\n');
TOL = 1e-6;
fprintf('Tolerence = %e set; it will be used in QR algorithm and testing the residuals. \n', TOL);

%% Define the test matrices
A1 = reshape(1:16,4,4)';
fprintf('First test matrix defined: A1 = \n');
disp(A1);
n = 10;
A2 = zeros(n);
A2(1,1) = 2; A2(1,2) = -1;
for i=2:n-1
    A2(i,i-1:i+1) = [-1, 2, -1];
end
A2(n,n-1) = -1; A2(n,n) = 2;
fprintf('Second test matrix defined: A2 = \n');
disp(A2);

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

%% LU

[P1,L1,U1] = my_lu(A1);
assert(norm(P1*A1-L1*U1, 1)<TOL, 'FAILED: PLU for 1st test matrix');
fprintf('TEST PASSED: PLU decomposition for 1st test matrix. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('L1-Norm of Residual (P*A1 - L*U) = %e\n', norm(P1*A1-L1*U1, 1));
fprintf('P = (in sparse form) \n');
disp(P1);
fprintf('L = \n');
disp(L1);
fprintf('U = \n');
disp(U1);
% [P2,L2,U2] = my_lu(A2);
% assert(sum(sum(abs(P2*A2-L2*U2)))<TOL, 'FAILED: PLU for 2nd test matrix');

%% Cholesky
G2 = my_cholesky(A2);
assert(norm(A2-G2*G2',1)<TOL, 'FAILED: Cholesky for 2nd test matrix');
fprintf('TEST PASSED: Cholesky decomposition for 2nd test matrix. >>>>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('L1-Norm of Residual (A2 - L*L\'') = %e\n', norm(A2-G2*G2', 1));
fprintf('L = (lower triangular indeed.) \n');
disp(G2);

%% Householder
[Q3, T3] = my_householder_trid(A3);
assert(norm(T3 - Q3'*A3*Q3,1)<TOL, 'FAILED: Householder for 3rd test matrix');
assert(norm(tril(T3,-2),1)<TOL, 'FAILED: Householder for 3rd test matrix');
fprintf('TEST PASSED: Householder Tridiagonalization for 3rd test matrix. >>>>>>>>>>>>>>>>>>\n');
fprintf('L1-Norm of Residual (T - Q\''*A3*Q) = %e\n', norm(T3 - Q3'*A3*Q3, 1));
fprintf('L1-Norm of Residual (Q*Q\''-I)      = %e  (Q is unitary indeed.) \n', norm(Q3*Q3'-eye(size(A3,1)),1));
fprintf('Q = \n');
disp(Q3);
fprintf('T = (tridiagonal indeed.) \n');
disp(T3);

%% QR with implicit Wilkinson shifts
[Q2,T2] = my_qr_alg(A2);
assert(norm(Q2'*A2*Q2-T2,1)<TOL, 'FAILED: QR algorithm for 2nd test matrix');
assert(norm(eig(A2)-sort(diag(T2)),1)<TOL, 'FAILED: QR algorithm for 2nd test matrix');
assert(norm(Q2*Q2'-eye(size(A2,1)),1)<TOL, 'FAILED: QR algorithm for 2nd test matrix');
fprintf('TEST PASSED: QR algorithm for 2nd test matrix. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('Supposedly the eigenvalues of A2 are 4*sin(0.5*pi*1:n).^2,     \n');
fprintf('(I have the full derivations done last year here: goo.gl/Lc1A9a\n');
fprintf('Just take hx = 1. )                                            \n');
fprintf('however due to the lack of Dirichlet boundary condition, the   \n');
fprintf('eigenvalues of A2 became rather uncanny; hence here we use     \n');
fprintf('MATLAB built-in EIG to compute the actual eigenvalues for      \n');
fprintf('comparison test.                                               \n');
fprintf('L1-Norm of Residual (Q\''*A2*Q-D)             = %e\n', norm(Q2'*A2*Q2-T2,1));
fprintf('L1-Norm of Residual (eig(A2)-sort(diag(D))) = %e  (D agree with MATLAB EIG results.) \n', norm(eig(A2)-sort(diag(T2)),1));
fprintf('L1-Norm of Residual (Q*Q\''-I)                = %e  (Q is unitary indeed.) \n', norm(Q2*Q2'-eye(size(A2,1)),1));
fprintf('Q = \n');
disp(Q2);
fprintf('D = (diagonal indeed.) \n');
disp(T2);

[Q3,T3] = my_qr_alg(A3);
assert(sum(sum(abs(Q3'*A3*Q3-T3)))<TOL, 'FAILED: QR algorithm for 3rd test matrix');
assert(sum(abs(eig(A3)-sort(diag(T3))))<TOL, 'FAILED: QR algorithm for 3rd test matrix');
assert(norm(Q3*Q3'-eye(size(A3,1)),1)<TOL, 'FAILED: QR algorithm for 3rd test matrix');
fprintf('TEST PASSED: QR algorithm for 3rd test matrix. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('L1-Norm of Residual (Q\''*A3*Q-D)             = %e\n', norm(Q3'*A3*Q3-T3,1));
fprintf('L1-Norm of Residual (eig(A3)-sort(diag(D))) = %e  (D agree with MATLAB EIG results.) \n', norm(eig(A3)-sort(diag(T3)),1));
fprintf('L1-Norm of Residual (Q*Q\''-I)                = %e  (Q is unitary indeed.) \n', norm(Q3*Q3'-eye(size(A3,1)),1));
fprintf('Q = \n');
disp(Q3);
fprintf('D = (diagonal indeed.) \n');
disp(T3);

fprintf('>>>>>>>>>>>>>>>>>>>>>>>>             All tests passed.             >>>>>>>>>>>>>>>>>>>>>>>>\n');
fprintf('>>>>>>>>>>>>>>>>>>>>>>>>  Math 270B Homework 2 Test Program Ends.  >>>>>>>>>>>>>>>>>>>>>>>>\n');
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