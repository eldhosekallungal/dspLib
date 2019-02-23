% square pulse
% Script to generate a square pulse from the basis forier series
% Amplitude = A
% Frequency = F
% duty cycle = k
% x(t) = ((A * k) / 2) + (A/pi) * sum(1/n * (1 - cos(2*pi*n*k))
%                               * sin(2*pi*n*F*t))
%                      + (A/pi) * sum(1/n * sin(2*pi*n*k)
%                               * cos(2*pi*n*F*t))

A = 1;
F = 1000;
k = 0.6;

F_s = 1000000;
NumSamples = 1000;

N = 200;

psd = zeros(1, N);

base_signal = signals(signals.sine, F_s);

x_t = zeros(1, NumSamples);

for i = 1:N
    base_signal.sine_prop.amplitude = (A / (i * pi)) * (1 - cos(2*pi*i*k));
    base_signal.sine_prop.frequency = i * F;
    base_signal.sine_prop.phase = 0;
    [x_s_t, ~] = base_signal.GetSamples(NumSamples);
    base_signal.sine_prop.amplitude = (A / (i * pi)) * sin(2*pi*i*k);
    base_signal.sine_prop.frequency = i * F;
    base_signal.sine_prop.phase = 90;
    [x_c_t, t_n] = base_signal.GetSamples(NumSamples);
    x_t = x_t + x_s_t + x_c_t;
    
    psd(i) = (1 / NumSamples) * (sum(x_s_t.*x_s_t) + sum(x_c_t .* x_c_t));
end

x_t = (A * k) + x_t;

plot(t_n, x_t);

figure;

stem(psd, '.');