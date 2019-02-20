
% Initialization testcase

% Features:
%  - Vector initialization using discrete values

A = [0 5 -2 15 3 3]; %! RFILE<> [0,0]
B = [3 15 3 14 0 2]; %! RFILE<> [0,0]
C = [0];             %! RFILE<> [0,0]

C(1) = A(3) + B(3); %! DPU [0,0]
