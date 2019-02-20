
% Min/Max Calculation

% Features:
%  - Maximum and minimum calculations on decreasing values

A = [34:3]; 	  %! RFILE<> [0,0]
B = zeros(1, 3);  %! RFILE<> [0,1]

B(1) = max(A); %! DPU [0,0]

B(2) = A(2) + A(3); %! DPU [0,0]

B(3) = min(A); %! DPU [0,0]
