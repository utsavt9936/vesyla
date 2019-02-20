
% DPU Chaining testcase

% Features:
%  - DPU Chaining for multiple vector operations

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 :-1: 14]; 	  %! RFILE<> [0,1]
E = [45 :-1: 14]; 	  %! RFILE<> [1,0]
D = zeros(1, 32); %! RFILE<> [1,1]
C1 = zeros(1, 32); %! CDPU<> [0,0]
C2 = zeros(1, 32); %! CDPU<> [0,1]

C1 = A + B;
C2 = C1 .* B;
D = E - C2; %! DPU [1,1]
