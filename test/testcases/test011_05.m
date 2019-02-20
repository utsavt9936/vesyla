
% Register transfer

% Features:
%  - Consecutive register transfers

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [0,2]
D = zeros(1, 32); %! RFILE<> [1,2]

B = A;
C = B;

D = B + C %! DPU [0,2]
