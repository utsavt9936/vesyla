
% DPU Chaining testcase

% Features:
%  - DPU Chaining for vector operation
%  - Use of the same vector in the input of both chained statements

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 :-1: 14]; 	  %! RFILE<> [0,1]
D = zeros(1, 32); %! RFILE<> [1,1]
C = zeros(1, 32); %! CDPU<> [1,0]

C = A + B;
D = C + A; %! DPU [0,1]
