
% Register transfer

% Features:
%  - Utilizing different cell locations

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

B = A;

C = B + A %! DPU [0,0]

