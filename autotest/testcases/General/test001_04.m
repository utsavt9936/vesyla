
% General testcase

% Features:
%  - Writing to the same register that is being read as the input of an arithmetic statement
%  - (All variables and operations allocated to one cell.)

A = [3 : 12]; %! RFILE<> [0,0]
B = [5 : 14]; %! RFILE<> [0,0]
C = [0];      %! RFILE<> [0,0]

C(1) = A(1) + B(2); %! DPU [0,0]
C(1) = C(1) + B(3); %! DPU [0,0]
