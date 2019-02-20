
% Min/Max Calculation

% Features:
%  - Minimum calculation on decreasing values
%  - zero value involved

A = [31:0]; 	  %! RFILE<> [0,0]
B = zeros(1, 1);  %! RFILE<> [0,1]

B = min(A); %! DPU [0,0]
