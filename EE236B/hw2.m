[t, y] = spline_data();
A = zeros(51,13);
G = zeros(51,13);
h = zeros(51,1);

for i=1:51
[y1,yp,ypp] = bsplines(t(i));
A(i,:) = y1';
G(i,:) = -ypp';
end

cvx_begin 
variable x(13)
minimize( (A*x-y)'*(A*x-y) )
subject to 
    G*x <= h
cvx_end

fit_x = linspace(0,10,1000);
fit_y = zeros(1,1000);
for i=1:1000
    fit_y(i) = x' * bsplines(fit_x(i));
end

plot(t,y,'rx', 'LineWidth', 2);
hold on
handle = plot(fit_x, fit_y, 'b-');
axis equal
saveas(handle,'EE236B_hw2_p58_fit','jpg');
hold off