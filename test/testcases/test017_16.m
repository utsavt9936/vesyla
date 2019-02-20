
% Calculation with accumulation testcase

% Features:
%  - Using several unconsecutive accumulation of subtraction operations
%  - Utilizing integer values

A = [11:20]; %! RFILE<> [0,0]
B = [1 2 3 1 1 4 9 11 7 8]; %! RFILE<> [0,0]
C = zeros(1, 4); %! RFILE<> [0,0]

C(1) = sum(A - B); %! DPU [0,0]

C(2) = C(1) + C(1);  %! DPU [0,0]
C(2) = sum(abs(A - B)); %! DPU [0,0]

C(3) = C(2) + C(2);  %! DPU [0,0]
C(3) = sum(B - A); %! DPU [0,0]

C(4) = C(3) + C(3);  %! DPU [0,0]
C(4) = sum(abs(B - A)); %! DPU [0,0]
