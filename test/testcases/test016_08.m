
% Min/Max Calculation

% Features:
%  - Consecutive maximum and minimum calculations on the same cell

A = [3:34]; 	  %! RFILE<> [0,0]
B = zeros(1, 3);  %! RFILE<> [0,1]

B(1) = max(A); %! DPU [0,0]

B(2) = min(A); %! DPU [0,0]
