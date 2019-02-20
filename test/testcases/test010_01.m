
% Memory testcase

% Features:
%  - Memory Read
%  - Reading one block of SRAM
%  - SRAM and Register File are in the same column.

M = [0 : 63]; 	  %! MEM<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,0]
X = zeros(1, 32); %! RFILE<> [1,0]

B(1:16) = M(1:16);

X = B + B; %! DPU[0,0]
