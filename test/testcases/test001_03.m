
% General testcase

% Features:
%  - Reading a value that has been written by another statement
%  - (All variables and operations allocated to one cell.)

A = [3 : 12]; %! RFILE<> [0,0]
B = [5 : 14]; %! RFILE<> [0,0]
C = [1 : 2 ]; %! RFILE<> [0,0]

C(1) = A(1) + B(1); %! DPU [0,0]
C(2) = C(1) + B(2); %! DPU [0,0]
