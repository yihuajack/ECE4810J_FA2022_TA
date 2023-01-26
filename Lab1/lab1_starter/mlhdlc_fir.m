%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MATLAB design: FIR Filter
% 
% Key Design pattern covered in this example: 
% (1) Implementation of a tap delay using a an array of persistent variables
% (2) Filter coefficients as a constant array
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%   Copyright 2011-2015 The MathWorks, Inc.

function outdatabuf=mlhdlc_fir(indatabuf)

% Load the filter coefficients
coeff = [  4.3723023e-003  8.5982873e-003  2.0507030e-002  4.1170253e-002  6.8559790e-002  9.7789676e-002  1.2244394e-001  1.3655872e-001  1.3655872e-001  1.2244394e-001  9.7789676e-002  6.8559790e-002  4.1170253e-002  2.0507030e-002  8.5982873e-003  4.3723023e-003];

persistent tap_delay;

% Clear tap delay line at beginning
if isempty(tap_delay)
  tap_delay = zeros(1,length(coeff));
end

% Perform sum of products
outdatabuf = tap_delay * coeff(end:-1:1)';

% Shift tap delay line
tap_delay = [tap_delay(2:length(coeff)) indatabuf];
