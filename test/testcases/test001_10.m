
% General testcase

% Features:
%  - Input/output pragma

A = [0  : 31]; 	  %! RFILE<input> [0,0]
B = [45 : 14]; 	  %! RFILE<input> [0,1]
C = zeros(1, 32); %! RFILE<output> [1,0]

C = A + B; %! DPU [0,0]
