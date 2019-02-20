
% DPU Chaining testcase

% Features:
%  - DPU Chaining for vector operation

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
E = [0  : 31]; 	  %! RFILE<> [0,2]
D = zeros(1, 32); %! RFILE<> [1,1]
C = zeros(1, 32); %! CDPU<> [0,1]

C = A + B;
D = C + E; %! DPU [1,1]
