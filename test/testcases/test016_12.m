
% Min/Max Calculation

% Features:
%  - Consecutive minimum and maximum calculations on different cells and different data

A1 = [3:18]; 	  %! RFILE<> [0,0]
A2 = [19:34]; 	  %! RFILE<> [1,0]
B = zeros(1, 3);  %! RFILE<> [0,1]

B(1) = min(A1); %! DPU [0,0]

B(2) = max(A2); %! DPU [1,0]

B(3) = max(A1); %! DPU [0,0]
