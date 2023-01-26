function mlhdlc_fir_tb
%

%   Copyright 2011-2015 The MathWorks, Inc.

close all

numSamples = 200;  % Number of input vectors
Fs = 44100;      % Sampling frequency in Hz
sinFreq = 1000; % Input sine frequency in Hz

% Create input data
data = 5 * sin( 2 * pi * (1:numSamples) / (Fs/sinFreq));
rng('default');
noise = 2*(rand(1,numSamples)-0.5);

indata = data + noise;
outdata = zeros(1, numSamples);

% Apply filter to each input sample
for n = 1:200
    
  % Call to design
  outdata(n) = mlhdlc_fir(indata(n));
  
end

figure('Name', [mfilename, '_io_plot']);
subplot(2,2,1); plot(data);
axis([1 numSamples -6 6]);
title(['Input = ',num2str(sinFreq),' Hz']);
subplot(2,2,2); plot(noise);
axis([1 numSamples -6 6]);
title('Noise');

% Plot input and output of filter
subplot(2,2,3); plot(indata);
axis([1 numSamples -6 6]);
title('Combined Input');
subplot(2,2,4); plot(outdata);
axis([1 numSamples -6 6]);
title('Filtered Output');

% Plot PSD of input and output
figure('Name', [mfilename, '_psd_plot']);
psdIn = pwelch(indata,64,[],[],Fs);
psdOut = pwelch(outdata,64,[],[],Fs);
hold off
plot(10*log10(psdIn))
hold on
plot(10*log10(psdOut),'r')
grid on
title('Input and Output PSD');
legend('Input','Output');
