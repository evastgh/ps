run('/Users/KoraJr/Documents/MATLAB/nonlin_meas_data.m');
D = zeros(299,300);
for k=1:299
    D(k,k) = -1;
    D(k,k+1) = 1;
end

cvx_begin
variables x(4) z(300)
minimize norm(A*x - z)
subject to 
    (1/beta)*D*y <= D*z
    D*z <= (1/alpha)*D*y
cvx_end