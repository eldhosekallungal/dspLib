
% Script to generate a square wave from the basis forier series
% Amplitude = A
% Frequency = F
% x(t) = 4* A/pi * sum(1/n * sin(n*2*pi*F*t)) | n = 1,3,5, ... etc

A = 1;
F = 1000;

F_s = 1000000;
NumSamples = 1000;

N = 10;

base_signal = signals(signals.sine, F_s);

x_t = zeros(1, NumSamples);

for i = 1:2:N
    base_signal.sine_prop.amplitude = (4 * A) / (i * pi);
    base_signal.sine_prop.frequency = i * F;
    [x_2_t, t_n] = base_signal.GetSamples(NumSamples);
    plot(t_n, x_2_t);
    hold on;
    x_t = x_t + x_2_t;
end

plot(t_n, x_t);

hold off;