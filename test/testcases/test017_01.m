
% Calculation with accumulation testcase

% Features:
%  - MAC operation
%  - Utilizing integer values

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 1); %! RFILE<> [1,0]

C = sum(A .* B); %! DPU [0,0]
