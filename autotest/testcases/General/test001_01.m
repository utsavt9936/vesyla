
% General testcase

% Features:
%  - Simple vector initialization and scalar addition
%  - (All variables and operations allocated to one cell.)

A = [3 : 12]; %! RFILE<> [0,0]
B = [5 : 14]; %! RFILE<> [0,0]
C = zeros(1,5);      %! RFILE<> [0,0]

C(1) = A(1) + B(1); %! DPU [0,0]
