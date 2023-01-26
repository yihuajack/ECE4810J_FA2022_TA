%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MATLAB design: Symmetric FIR Filter
% 
% Introduction:
%
% We can reduce the complexity of the FIR filter by leveraging its symmetry. 
% Symmetry for an n-tap filter implies, coefficient h0 = coefficient hn-1, 
% coefficient, h1 = coefficient hn-2, etc. In this case, the number of 
% multipliers can be approximately halved. The key is to add the 
% two data values that need to be multiplied with the same coefficient 
% prior to performing the multiplication. 
%
% Key Design pattern covered in this example: 
% (1) Filter states represented using the persistent variables
% (2) Filter coefficients passed in as parameters

%   Copyright 2011-2019 The MathWorks, Inc.

%#codegen
function [y_out, delayed_xout] = mlhdlc_sfir(x_in,h_in1,h_in2,h_in3,h_in4)   
% Symmetric FIR Filter

% declare and initialize the delay registers
persistent ud1 ud2 ud3 ud4 ud5 ud6 ud7 ud8;
if isempty(ud1)
    ud1 = 0; ud2 = 0; ud3 = 0; ud4 = 0; ud5 = 0; ud6 = 0; ud7 = 0; ud8 = 0;
end

% access the previous value of states/registers
a1 = ud1 + ud8; a2 = ud2 + ud7;
a3 = ud3 + ud6; a4 = ud4 + ud5;

% multiplier chain
m1 = h_in1 * a1; m2 = h_in2 * a2;
m3 = h_in3 * a3; m4 = h_in4 * a4;

% adder chain
a5 = m1 + m2; a6 = m3 + m4;

% filtered output
y_out = a5 + a6;

% delayout input signal
delayed_xout = ud8;

% update the delay line
ud8 = ud7; 
ud7 = ud6;
ud6 = ud5;
ud5 = ud4;
ud4 = ud3;
ud3 = ud2;
ud2 = ud1;
ud1 = x_in;
end