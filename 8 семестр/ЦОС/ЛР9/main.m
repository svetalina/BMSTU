I = imread('im3.bmp');

figure;

imshow(I);title('Изображение');

spectrum = fftshift(fft2(I));

W = spectrum .* spectrum;

cepstrum = 1/5*log(1 + abs(W));

figure;
imshow(mat2gray(1+abs(cepstrum)));title('Кепстр');

[maxVal, maxIdx] = max(cepstrum(:));
[maxRow, maxCol] = ind2sub(size(cepstrum), maxIdx);

N = size(I);
P = [maxCol - N(2)/2, N(1)/2 - maxRow];
theta = atan2(P(2), P(1)) * 180/pi;

central_row = cepstrum(maxRow,:);

len = size(central_row);

half_row = central_row(len(2)/2:end);

[pks, locs] = findpeaks(half_row);

c = 6;
a = c * sind(abs(theta));
b = sqrt(c * c - a * a);

PSF = fspecial('motion', 2, theta);

output = deconvlucy(I, PSF, 100);

figure;
imshow(output);title('Результат');