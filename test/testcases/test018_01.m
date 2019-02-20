
% DPU Chaining testcase

% Features:
%  - DPU Chaining for scalar operation

A = [0  : 31]; %! RFILE<> [0,0]
B = [45 : 14]; %! RFILE<> [0,1]
C = [0]; 	   %! CDPU<> [0,0]

C = A(2) + B(2);
B(1) = C + A(5); %! DPU [0,1]
