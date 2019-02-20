
% Register transfer

% Features:
%  - Utilizing different cell locations

A = [0  : 31]; 	  %! RFILE<> [1,2]
B = zeros(1, 32); %! RFILE<> [0,0]
C = zeros(1, 32); %! RFILE<> [0,1]

B = A;

C = B + A %! DPU [0,0]

