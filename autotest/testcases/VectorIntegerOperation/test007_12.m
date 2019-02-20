
% Vector integer operation testcase

% Features:
%  - Using different DPU modes on the same DPU

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]
D = zeros(1, 32); %! RFILE<> [1,1]

C = A + B; %! DPU [0,0]
D = C .* A; %! DPU [0,0]
