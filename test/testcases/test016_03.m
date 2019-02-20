
% Min/Max Calculation

% Features:
%  - Minimum and maximum calculations on the same cell

A = [3:34]; 	  %! RFILE<> [0,0]
B = zeros(1, 3);  %! RFILE<> [0,1]

B(1) = min(A); %! DPU [0,0]

B(2) = A(2) + A(3); %! DPU [0,0]

B(3) = max(A); %! DPU [0,0]
