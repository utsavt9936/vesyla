
% Vector integer operation testcase

% Features:
%  - Having several consecutive read accesses to the same vector variable
%  - Using the same DPU

A = [0  : 31]; 	  %! RFILE<> [0,0]
C = zeros(1, 32); %! RFILE<> [1,0]
D = zeros(1, 32); %! RFILE<> [1,1]

C = A + A; %! DPU [0,0]
D = A + A; %! DPU [0,0]
