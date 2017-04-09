%% Problem 1
clear all;
clc;
circlefit;
A = [-2*u, -2*v, ones(50,1)];
b = -u.^2-v.^2;
x = A\b;
R = sqrt(x(1)^2+x(2)^2-x(3));
theta = linspace(0,2*pi, 1000);
circle_x = x(1) + R*cos(theta);
circle_y = x(2) + R*sin(theta);
handle = plot(circle_x, circle_y, 'b-');
hold on
handle = plot(u,v,'rx', 'LineWidth', 2);
axis equal
saveas(handle,'hw1_p1','jpg');
hold off


%% Problem 2
clear all;
clc;
illumdata;
[n,m] = size(A);
sample_size = 100;

%(a) Equal lamp powers
f0 = @(p) max(abs(log(A*p)));
fa = @(gamma) f0(gamma*ones(m,1));
gamma = linspace(0,1,sample_size);
fa_gamma = zeros(1,sample_size);
for i=1:sample_size
fa_gamma(i) = fa(gamma(i));
end
handle_a = plot(gamma, fa_gamma,'b');
saveas(handle_a, 'hw1_p2_a','jpg');

[obja,index] = min(fa_gamma);
pa = gamma(index)*ones(m,1);

%(b) Least-squares with saturation
pb = A\ones(n,1);
for i=1:m
    if pb(i) > 1
        pb(i) = 1;
    end
    if pb(i) < 0
        pb(i) = 0;
    end
end
objb = f0(pb);

%(c) Regularized least-squares
for rho=linspace(0,1,21)
    pc = (A'*A + rho*eye(m))\(A'*ones(n,1)+0.5*rho*ones(m,1));
    if pc > zeros(m,1) & pc < ones(m,1)
        break
    end
end        
objc = f0(pc);

%(d) Chebyshev approximation
cvx_begin
    variable pd(m)
    minimize( norm(A*pd-1, inf) )
    subject to
        pd <= ones(m,1)
        pd >= zeros(m,1)
cvx_end
objd = f0(pd);

%(e) Piecewise-linear approximation
h_pwl = @(u) max([u;2/0.5-1/0.5/0.5*u;2/0.8-1/0.8/0.8*u;2-u]);
cvx_begin
    variable pe(m)
    minimize( max(h_pwl((A*pe)')) )
    subject to
        pe <= ones(m,1)
        pe >= zeros(m,1)
cvx_end
obje = f0(pe);

%(f) Exact solution
cvx_begin
    variable pf(m)
    minimize( max(max(A*pf, inv_pos(A*pf))) )
    subject to
        pf <= ones(m,1)
        pf >= zeros(m,1)
cvx_end    
objf = f0(pf);

% plot
obj = [obja;objb;objc;objd;obje;objf];
handle = plot(1:6,obj, 'o-');
saveas(handle, 'hw1_p2', 'jpg');





