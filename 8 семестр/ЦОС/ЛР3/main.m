function lab_03()
T = 2.0;
A = 1.0;
sigma = 1.0;

mult = 5;
step = 0.05;
t = -mult:step:mult;

function y = rectpls(x,T,A)
    y = zeros(size(x));
    y(abs(x) - T < 0) = A;
    y(abs(x) == T) = A/2;
end

function y = gauspls(x,A,s)
	y = A * exp(-(x/s).^2);
end

x1 = [rectpls(t,T,A) zeros(1,length(t))];
x2 = [gauspls(t,A,sigma) zeros(1,length(t))];
x3 = [rectpls(t,T/2,A/2) zeros(1,length(t))];
x4 = [gauspls(t,A/2,sigma/2) zeros(1,length(t))];

y1 = ifft(fft(x1).*fft(x2))*step;
y2 = ifft(fft(x1).*fft(x3))*step;
y3 = ifft(fft(x2).*fft(x4))*step;

start = fix((length(y1)-length(t))/2);
y1 = y1(start+1:start+length(t));
y2 = y2(start+1:start+length(t));
y3 = y3(start+1:start+length(t));


figure(1)
plot(t,x1(1:201),'m',t,x2(1:201),'g',t,y1);
title('Прямоугольная и Гауссова свертка');
legend('П','Г','Свертка');

figure(2)
plot(t,x1(1:201),'m',t,x3(1:201),'g',t,y2);
title('Прямоугольные свертки');
legend('П1','П2','Свертка');

figure(3)
plot(t,x2(1:201),'m',t,x4(1:201),'g',t,y3);
title('Гауссовы свертки');
legend('Г1','Г2','Свертка');
end