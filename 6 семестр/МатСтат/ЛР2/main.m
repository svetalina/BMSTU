    X = [12.80,10.91,10.69,10.46,13.08,11.35,13.07,12.46,13.29,11.09,...
        10.34,12.57,12.99,12.28,12.62,12.43,12.06,13.72,11.64,11.81,...
        10.47,13.94,13.31,13.31,11.11,11.06,11.84,12.28,13.14,9.80,...
        11.27,12.56,11.15,11.65,11.92,11.31,12.07,12.06,11.53,12.04,...
        12.44,13.89,10.72,11.75,11.14,12.70,13.64,12.64,11.37,10.12,...
        11.87,13.86,12.53,12.52,10.65,9.84,11.15,9.54,11.39,11.57,...
        14.00,10.98,10.81,12.11,12.24,10.42,15.21,13.00,11.63,11.40,...
        13.41,10.78,11.98,12.51,12.95,11.59,11.04,10.99,11.91,10.72,...
        11.74,11.82,12.45,11.70,12.49,12.10,10.99,12.58,12.99,10.09,...
        12.00,13.19,12.89,11.72,13.80,11.37,12.15,10.98,11.93,10.83,...
        12.41,12.52,12.21,12.82,12.38,11.59,13.60,12.82,13.52,13.73,...
        12.53,10.78,13.69,10.41,11.13,11.28,11.28,10.40,10.47,10.51];
    X = [X X];
    n = length(X);

% Вычисление выборочного среднего
    mu = sum(X) / n;
    fprintf("Выборочное среднее = %.4f\n", mu);
    
% Вычисление исправленной выборочной дисперсии
    if (n > 1)
        s2 = sum((X - mu) .^2) / (n - 1);
    else
        s2 = 0;
    end

    fprintf("Исправленная выборочная дисперсия = %.4f\n", s2);
    

    gamma = 0.9;
    alpha = (1 - gamma) / 2;

    fprintf("\ngamma = %.1f\n", gamma);
    
 % Вычисление доверительных интервалов

    quant_st = tinv((1 - alpha), (n - 1));
    
    lower_m = mu - (quant_st * sqrt(s2) / sqrt(n));
    upper_m = mu + (quant_st * sqrt(s2) / sqrt(n));

    fprintf("\ngamma-доверительный интервал для mu: (%.4f, %.4f)\n", lower_m, upper_m);
    

    quant_xi2_lower = chi2inv((1 - alpha), (n - 1));
    quant_xi2_upper = chi2inv(alpha, (n - 1));
    
    lower_sigma = s2 * (n - 1) / quant_xi2_lower;
    upper_sigma = s2 * (n - 1) / quant_xi2_upper;

    fprintf("\ngamma-доверительный интервал для sigma: (%.4f, %.4f)\n", lower_sigma, upper_sigma);
    
 % Построение графиков 3.a)
    
    mu_arr = zeros(n, 1);
    s2_arr = zeros(n, 1);
    
    for i = 1 : n
        X_part = X(1 : i);

        mu_arr(i) = sum(X_part) / i;

        if (i > 1)
            s2_arr(i) = sum((X_part - mu_arr(i)) .^2) / (i - 1);
        else
            s2_arr(i) = 0;
        end
    end
    
    mu_line = zeros(n, 1);
    mu_line(1 : n) = mu_arr(n);
    
    mu_lower = zeros(n, 1);
    mu_upper = zeros(n, 1);
    
    for i = 1 : n
        quant_st = tinv((1 - alpha), (i - 1));

        mu_lower(i) = mu_arr(i) - (quant_st * sqrt(s2_arr(i)) / sqrt(i));
        mu_upper(i) = mu_arr(i) + (quant_st * sqrt(s2_arr(i)) / sqrt(i)); 
    end
    
    plot((10 : n), mu_line(10 : n), 'r', 'LineWidth', 1);
    hold on;
    plot((10 : n), mu_arr(10 : n), 'g', 'LineWidth', 1);
    hold on;
    plot((10 : n), mu_upper(10 : n), 'b', 'LineWidth', 1);
    hold on;
    plot((10 : n), mu_lower(10 : n), 'k', 'LineWidth', 1);
    hold on;
    
    grid on;
    xlabel("n");
    ylabel('\mu');

    legend('\mu\^(x_N)', '\mu\^(x_n)', '\mu^{-}(x_n)', '\mu_{-}(x_n)');

% Построение графиков для задания 3.b)

    figure()
    
    mu_arr = zeros(n, 1);
    s2_arr = zeros(n, 1);
    
    for i = 1 : n
        X_part = X(1 : i);

        mu_arr(i) = sum(X_part) / i;

        if (i > 1)
            s2_arr(i) = sum((X_part - mu_arr(i)) .^2) / (i - 1);
        else
            s2_arr(i) = 0;
        end
    end
    
    s2_line = zeros(n, 1);
    s2_line(1 : n) = s2_arr(n);
    
    s2_lower = zeros(n, 1);
    s2_upper = zeros(n, 1);
    
    for i = 1 : n
        quant_xi2_lower = chi2inv((1 - alpha), (i - 1));
        quant_xi2_upper = chi2inv(alpha, (i - 1));

        s2_lower(i) = s2_arr(i) * (i - 1) / quant_xi2_lower;
        s2_upper(i) = s2_arr(i) * (i - 1) / quant_xi2_upper; 
    end
    
    plot((10 : n), s2_line(10 : n), 'r', 'LineWidth', 1);
    hold on;
    plot((10 : n), s2_arr(10 : n), 'g', 'LineWidth', 1);
    hold on;
    plot((10 : n), s2_upper(10 : n), 'b', 'LineWidth', 1);
    hold on;
    plot((10 : n), s2_lower(10 : n), 'k', 'LineWidth', 1);
    hold on;
    
    grid on;
    xlabel("n");
    ylabel('\sigma');
    
    legend('S^2(x_N)', 'S^2(x_n)', '\sigma^{2 -}(x_n)', '\sigma^2_{-}(x_n)');
