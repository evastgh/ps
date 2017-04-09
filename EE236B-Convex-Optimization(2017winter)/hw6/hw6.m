rand('state',0);
n = 40;
x = 30 * rand(1,n);
y = 30 * rand(1,n);

N = 400;
theta = linspace(-pi,pi,N)';
theta_tar = pi/12;
[~, tar_k] = min(abs(theta-theta_tar));
theta_tar_approx = theta(tar_k);
Delta = pi/12;
outside_index = (abs(theta-theta_tar)>= Delta);
G = @(omega) exp(1i*(cos(theta)*x+sin(theta)*y))*omega;
G_tar = @(omega) exp(1i*(cos(theta_tar_approx)*x+sin(theta_tar_approx)*y))*omega;

cvx_begin
    variable omega(n) complex
    variable t
    minimize t;
    subject to
        diag(outside_index)*abs(G(omega)) <= t*ones(N,1)
        G_tar(omega) == 1
cvx_end

h=semilogy(abs(G(omega)),'b-','LineWidth',1.2);
saveas(h, 'hw6P126','jpg');