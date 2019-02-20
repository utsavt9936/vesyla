
% Memory testcase

% Features:
%  - Memory Read
%  - Reading two blocks of SRAM using two separate SRAM instructions

M = [0 : 63]; 	  %! MEM<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,0]
X = zeros(1, 32); %! RFILE<> [1,0]

B(1:16)  = M(1:16);
B(17:32) = M(17:32);

X = B + B; %! DPU[0,0]
