Signal = signals(signals.sine, 10000);
base = 25;
amp = 1;
N = zeros(1,1000);

for i = 1:100
    Signal.sine_prop.frequency = base * i;
    Signal.sine_prop.amplitude = amp / i;
    [n, t] = Signal.GetSamples(1000);
    N = N + n;
end

plot(t, N);
