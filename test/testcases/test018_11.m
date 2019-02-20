
% DPU Chaining testcase

% Features:
%  - DPU Chaining for vector operation
%  - Having different operation types in the chain

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
D = zeros(1, 32); %! RFILE<> [1,1]
C = zeros(1, 32); %! CDPU<> [1,0]

C = A + B;
D = C .* A; %! DPU [0,1]
