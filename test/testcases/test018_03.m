
% DPU Chaining testcase

% Features:
%  - DPU Chaining for scalar operation
%  - Selecting a different cell for the final destination

A = [0  : 31]; %! RFILE<> [0,0]
B = [45 : 14]; %! RFILE<> [0,1]
D = [0]; 	   %! RFILE<> [1,1]
C = [0]; 	   %! CDPU<> [1,0]

C = A(2) + B(2);
D = C + A(5); %! DPU [0,1]
