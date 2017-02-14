clear all;
fprintf('Here comes the matrix instanciation runtime. \n');
%% dense instanciation with pre-allocated memory using ZEROS
tic;
A1 = zeros(1000);
A1(1,1) = -1;
A1(1,2) = 1;
for i=2:999
    A1(i,i-1) = 1;
    A1(i,i) = -2;
    A1(i,i+1) = 1;
end
A1(1000,999) = 1;
A1(1000,1000) = -1;
toc;

%% dense instanciation without pre-allocated memory
%  (memory of assigned to the matrix is resized in every iteration)
tic;
% A2 = zeros(1000);
A2(1,1) = -1;
A2(1,2) = 1;
for i=2:999
    A2(i,i-1) = 1;
    A2(i,i) = -2;
    A2(i,i+1) = 1;
end
A2(1000,999) = 1;
A2(1000,1000) = -1;
toc;

%% dense instanciation using DIAG
tic;
A3 = diag(-2*ones(1000,1)) + ...
     diag(ones(999,1),1) + ...
     diag(ones(999,1),-1);
A3(1,1) = -1;
A3(1000,1000) = -1;
toc;

%% sparse instanciation
%  (column specific)
tic;
sparse_i = zeros(3000,1);
sparse_j = zeros(3000,1);
sparse_content = zeros(3000,1);
nonzero_entry = 0;

nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 1;
sparse_j(nonzero_entry) = 1;
sparse_content(nonzero_entry) = -1;
nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 2;
sparse_j(nonzero_entry) = 1;
sparse_content(nonzero_entry) = 1;
for j=2:999
    nonzero_entry = nonzero_entry + 1;
    sparse_i(nonzero_entry) = j-1;
    sparse_j(nonzero_entry) = j;
    sparse_content(nonzero_entry) = 1;
    nonzero_entry = nonzero_entry + 1;
    sparse_i(nonzero_entry) = j;
    sparse_j(nonzero_entry) = j;
    sparse_content(nonzero_entry) = -2;
    nonzero_entry = nonzero_entry + 1;
    sparse_i(nonzero_entry) = j+1;
    sparse_j(nonzero_entry) = j;
    sparse_content(nonzero_entry) = 1;
end
nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 999;
sparse_j(nonzero_entry) = 1000; 
sparse_content(nonzero_entry) = 1;
nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 1000;
sparse_j(nonzero_entry) = 1000; 
sparse_content(nonzero_entry) = -1;
A4 = sparse(sparse_i(1:nonzero_entry),...
            sparse_j(1:nonzero_entry),...
            sparse_content(1:nonzero_entry),...
            1000,1000,3000);
toc;
clear sparse_i sparse_j sparse_content nonzero_entry

%% sparse instanciation
%  (row specific)
tic;
sparse_i = zeros(3000,1);
sparse_j = zeros(3000,1);
sparse_content = zeros(3000,1);
nonzero_entry = 0;

nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 1;
sparse_j(nonzero_entry) = 1;
sparse_content(nonzero_entry) = -1;
nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 1;
sparse_j(nonzero_entry) = 2;
sparse_content(nonzero_entry) = 1;
for i=2:999
    nonzero_entry = nonzero_entry + 1;
    sparse_i(nonzero_entry) = i;
    sparse_j(nonzero_entry) = i-1;
    sparse_content(nonzero_entry) = 1;
    nonzero_entry = nonzero_entry + 1;
    sparse_i(nonzero_entry) = i;
    sparse_j(nonzero_entry) = i;
    sparse_content(nonzero_entry) = -2;
    nonzero_entry = nonzero_entry + 1;
    sparse_i(nonzero_entry) = i;
    sparse_j(nonzero_entry) = i+1;
    sparse_content(nonzero_entry) = 1;
end
nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 1000;
sparse_j(nonzero_entry) = 999; 
sparse_content(nonzero_entry) = 1;
nonzero_entry = nonzero_entry + 1;
sparse_i(nonzero_entry) = 1000;
sparse_j(nonzero_entry) = 1000; 
sparse_content(nonzero_entry) = -1;
A5 = sparse(sparse_i(1:nonzero_entry),...
            sparse_j(1:nonzero_entry),...
            sparse_content(1:nonzero_entry),...
            1000,1000,3000);
toc;

fprintf('Here comes the multiplication runtime. \n');
x = ones(1000,1);
tic; x1 = A1*x; toc;
tic; x2 = A2*x; toc;
tic; x3 = A3*x; toc;
tic; x4 = A4*x; toc;
tic; x5 = A5*x; toc;
fprintf('norm(x1) = %f\n',norm(x1));
fprintf('norm(x2) = %f\n',norm(x1));
fprintf('norm(x3) = %f\n',norm(x1));
fprintf('norm(x4) = %f\n',norm(x1));
fprintf('norm(x5) = %f\n',norm(x1));