
% Initialization testcase

% Features:
%  - Initialization using zeros() function

A = zeros(1, 10);    %! RFILE<> [0,0]
B = [3 15 3 14 0 2]; %! RFILE<> [0,0]
C = zeros(1, 6);     %! RFILE<> [0,0]

C = A(3:8) + B; %! DPU [0,0]
