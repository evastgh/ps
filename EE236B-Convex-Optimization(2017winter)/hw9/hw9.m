one_bit_meas_data;
[m,n] = size(A);
for i=1:50
    if y(i) > 0
        A(i,:) = -A(i,:);
        b(i) = -b(i);
        y(i) = -y(i);
    end
end
Q = @(s) 0.5*erfc(-s/sqrt(2));
% dQ = @(s) 1/sqrt(2*pi)*exp(-0.5*s^2);
% ddQ = @(s) -s/sqrt(2*pi)*exp(-0.5*s^2);
l = @(x) sum(log(Q(b-A*x)));
f = @(x) -sum(log(Q(b-A*x)));

max_iter = 1000;
TOL = 1e-5;
alpha = 0.2; %(0.01, 0.3)
beta = 0.5; %(0.1, 0.8)

x = rand(n,1);
for iter = 1:max_iter
    z = b-A*x;
    df = zeros(n,1);
    H = zeros(n);
    for i=1:m
        df = df + sqrt(2/pi)/erfcx(-z(i)/sqrt(2)) * A(i,:)';
        H = H + (z(i)*sqrt(2/pi)/erfcx(-z(i)/sqrt(2)) + (sqrt(2/pi)/erfcx(-z(i)/sqrt(2))^2)) * A(i,:)'*A(i,:);
    end
    dx = - H \ df;
    lsq = df' * (-dx);
    if lsq <= 2*TOL
        break
    end
    t = 1;
    while f(x + t*dx) > f(x) - alpha * t * lsq
        t = beta * t;
    end
    x = x + t * dx;
    x_data(:,iter) = x;
    l_data(iter) = l(x);
end
h1 = plot(1:iter-1,l_data(1:iter-1));
saveas(h1,'hw9P89','jpg');
