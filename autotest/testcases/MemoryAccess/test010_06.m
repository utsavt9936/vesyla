
% Memory testcase

% Features:
%  - Memory Read
%  - Modifying SRAM location

M = [0 : 63]; 	  %! MEM<> [0,2]
B = zeros(1, 32); %! RFILE<> [0,0]
X = zeros(1, 32); %! RFILE<> [1,0]

B = M(1:32);

X = B + B; %! DPU[0,0]
