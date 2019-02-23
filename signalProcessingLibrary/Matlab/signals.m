classdef signals < handle
    %UNTITLED2 Summary of this class goes here
    %   Detailed explanation goes here
    properties(Constant)
        % defines the types of waveforms
        step = 0;
        ramp = 1;
        sine = 2;
        pulse = 3;
        square = 4;
        sawtooth = 5; 
    end
    properties(SetAccess = private, GetAccess = public)
        Type
        SamplingFrequency
        SignalAmplitude
        SignalFrequency = 0;
    end
    properties(SetAccess = public, GetAccess = public)
        step_prop = struct('amplitude', 1);
        ramp_prop = struct('slope', 45);
        sine_prop = struct('amplitude', 1, 'frequency', 1000, 'phase', 0);
        pulse_prop = struct('amplitude', 1, 'frequency', 1000, 'width', 0.5);
        square_prop = struct('amplitude', 1, 'frequency', 1000, 'width', 0.5);
        sawtooth_prop = struct('amplitude', 1, 'frequency', 1000, 'width', 0.5);
    end
    methods
        function self = signals(Type, SamplingFrequency)
            self.Type = Type;
            self.SamplingFrequency = SamplingFrequency;
        end
        function T_n = GetTimeSamples(self, NumSamples)
            T_s = 1 / self.SamplingFrequency;
            T_N = T_s * NumSamples;
            T_n = [0:T_s:(T_N - T_s)];
        end
        function [samples, T_n] = GetSamples(self, NumSamples)
            T_s = 1 / self.SamplingFrequency;
            T_N = T_s * NumSamples;
            T_n = [0:T_s:(T_N - T_s)];
            switch self.Type
                case signals.step
                    samples = self.SignalAmplitude * ones(1, NumSamples);
                case signals.ramp
                    samples = tand(self.ramp_prop.slope) .* T_n;
                case signals.sine
                    samples = self.sine_prop.amplitude *...
                        sin((2 * pi * self.sine_prop.frequency * T_n)...
                        + ((pi / 180) * self.sine_prop.phase));
            end
        end
    end
    
end

