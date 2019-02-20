
% General testcase

% Features:
%  - Having 3 arithmetic statements
%  - (All variables and operations allocated to one cell.)

A = [3 : 12]; %! RFILE<> [0,0]
B = [5 : 14]; %! RFILE<> [0,0]
C = [0 0 0];  %! RFILE<> [0,0]

C(1) = A(1) + B(1); %! DPU [0,0]
C(2) = A(2) + B(2); %! DPU [0,0]
C(3) = A(5) + B(8); %! DPU [0,0]
