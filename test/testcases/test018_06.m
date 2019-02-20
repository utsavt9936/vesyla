
% DPU Chaining testcase

% Features:
%  - DPU Chaining for multiple scalar operations

A = [0  : 31]; %! RFILE<> [0,0]
B = [45 : 14]; %! RFILE<> [0,1]
D = [0]; 	   %! RFILE<> [1,1]
C1 = [0]; 	   %! CDPU<> [1,0]
C2 = [0]; 	   %! CDPU<> [1,1]

C1 = A(2) + B(2);
C2 = A(5) - C1;
D  = A(6) * C2 %! DPU [0,1]
