
% Min/Max Calculation

% Features:
%  - Minimum calculation
%  - zero value involved

A = [0:31]; 	  %! RFILE<> [0,0]
B = zeros(1, 1);  %! RFILE<> [0,1]

B = min(A); %! DPU [0,0]
