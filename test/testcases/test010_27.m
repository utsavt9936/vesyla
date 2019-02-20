
% Memory testcase

% Features:
%  - Memory Read/Write
%  - Writing to memory after reading from it
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

BLOCK_SIZE = 16;

M = [0 : 255]; 	  %! MEM<> [0,0]
A = zeros(1, BLOCK_SIZE); %! RFILE<> [0,0]

A = M(1:BLOCK_SIZE);

A(4) = A(1) + A(2); %! DPU[0,0]

M(1:BLOCK_SIZE) = A;
