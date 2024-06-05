function lab04
  sigma = 0.5;

  t_max = 5;
  dt = 0.01;
  t = -t_max:dt:t_max;

  x0 = gaussian(t, sigma);

  NA = 0;
  NS = 0.05;
  n1 = normrnd(NA, NS, [1 length(x0)]);
  x1 = x0 + n1;

  count = 7;
  M = 0.4;
  n2 = impulse_noise(length(x0), count, M);
  x2 = x0 + n2;

  % Фильтрация
  G = gaussian_filter_low(4, 20);
  B = butterworth_filter_low(6, 20);

    figure(3);

  plot_figure(0, t, x0, x1, x2, 'Исходный сигнал')
  plot_figure(1, t, x0, filtfilt(G, 1, x1), filtfilt(G, 1, x2), 'Фильтр Гаусса')
  plot_figure(2, t, x0, filtfilt(B, 1, x1), filtfilt(B, 1, x2), 'Фильтр Баттерворта')
end

function plot_figure(i, t, x0, x1, x2, tit)
  subplot(9, 1, 3*i+1);
  plot(t, x0);
  title(tit);
  legend('Без помех');

  subplot(9, 1, 3*i+2);
  plot(t, x1);
  title(tit);
  legend('Гауссовы помехи');

  subplot(9, 1, 3*i+3);
  plot(t, x2);
  title(tit);
  legend('Импульсные помехи');
  % print(strcat('plot04_', num2str(i)), '-dpng');
end

% Gaussian pulse generation
function y = gaussian(x, sigma)
  y = exp(-(x / sigma) .^ 2);
end

% Impulsive noise generation
function y = impulse_noise(size, N, mult)
  step = floor(size / N);
  y = zeros(1, size);
  for i = 1:floor(N / 2)
    y(round(size / 2) + i * step) = mult * (0.5 + rand);
    y(round(size / 2) - i * step) = mult * (0.5 + rand);
  end
end

function y = butterworth_filter_low(D, size)
  x = linspace(-size / 2, size / 2, size);
  y = 1 ./ (1 + (x ./ D).^4);
  y = y / sum(y);
end

function y = gaussian_filter_low(sigma, size)
  x = linspace(-size / 2, size / 2, size);
  y = exp(-x.^2 / (2 * sigma^2));
  y = y / sum(y);
end