f=@(x) max(abs(x), 2*abs(x)-1);
F=@(u) sum(f(u));
A = [-1,0.4,0.8;1,0,0;0,1,0];
b = [1;0;0.3];
x_des = [7;2;-6];
N = 30;
KAb = zeros(3,30);
KAb(:,30) = b;
for i=29:-1:1
    KAb(:,i) = A * KAb(:, i+1);
end

cvx_begin
    variable u(N);
    minimize F(u);
    subject to 
        KAb*u == x_des;
cvx_end
plot(0:29,u','-b');

clear u
%% alternative solution (LP)
cvx_begin
    variable u(2*N);
    minimize ones(1,N)*u(N+1:end);
    subject to
        KAb*u(1:N) == x_des;
        u(1:N) <= u(N+1:end);
        -u(1:N) <= u(N+1:end);
        2*u(1:N)-ones(N,1) <= u(N+1:end);
        -2*u(1:N)-ones(N,1) <= u(N+1:end);
cvx_end
hold on
handle = plot(0:29,u(1:N)','mx','LineWidth',1.2);
saveas(handle, 'hw3_p317','jpg');