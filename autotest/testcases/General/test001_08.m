
% General testcase

% Features:
%  - Mapping variables to more than one cell

A = [3 : 12]; %! RFILE<> [0,1]
B = [5 : 14]; %! RFILE<> [0,0]
C = [0 0];    %! RFILE<> [1,0]

C(1) = A(1) + B(1); %! DPU [0,0]
C(2) = A(2) + B(2); %! DPU [0,0]
