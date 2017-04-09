%% Problem A7.9
% P = zeros(3,4,4);
% P(:,:,1) = [1 0 0 0; 0 1 0 0; 0 0 1 0];
% P(:,:,2) = [1 0 0 0; 0 0 1 0; 0 -1 0 10];
% P(:,:,3) = [1 1 1 -10; -1 1 1 0; -1 -1 1 10];
% P(:,:,4) = [0 1 1 0; 0 -1 1 0; -1 0 0 10];
% 
% y = zeros(2,4);
% y(:,1) = [.98; .93];
% y(:,2) = [1.01; 1.01];
% y(:,3) = [.95; 1.05];
% y(:,4) = [2.04; 0];
% 
% f = @(x,k) (P(1:2,:,k)*[x;1])/(P(3,:,k)*[x;1]);
% g = @(x) max([norm(f(x,1)-y(:,1)), norm(f(x,2)-y(:,2)), norm(f(x,3)-y(:,3)), norm(f(x,4)-y(:,4))]);
% 
% 
% phi_k = @(t,x,k) norm(P(1:2,:,k)*[x;1]-y(:,k)*P(3,:,k)*[x;1]) - t*P(3,:,k)*[x;1];
% phi = @(t,x) max([phi_k(t,x,1), phi_k(t,x,2), phi_k(t,x,3), phi_k(t,x,4)]);
% TOL = 1e-4;
% l = 0;  % objective function is always nonnegative
% u = 1;  % random upper bound
% num_iter = 0;
% while u-l > TOL
%     num_iter = num_iter + 1;
%     t = 0.5 * (u + l);
%     cvx_begin
%         variable x(3);
%         minimize 1;
%         subject to
%             phi(t,x) <= 0;
%     cvx_end
%     p_star(num_iter) = g(x);
%     u_data(num_iter) = u;
%     l_data(num_iter) = l;
%     if cvx_optval == 1
%         u = t;
%     else
%         l = t;
%     end
% end
% h1 = plot(p_star,'LineWidth', 1.1);
% title('p*');
% saveas(h1,'hw4A79_pstar','jpg');
% 
% figure;
% semilogy(u_data,'b-x','LineWidth',1.05);
% hold on;
% h2 = semilogy(l_data,'r-x','LineWidth',1.05);
% title('bisection process');
% saveas(h2, 'hw4A79_bisection', 'jpg');

%% Problem A14.8
spacecraft_landing_data;
