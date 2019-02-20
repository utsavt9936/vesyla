% Memory testcase

% Features:
%  - Memory Read/Write
%  - Writing to memory after reading from it
%  - SRAM and Register File are in different columns (distance=2).
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.
%  - (1,4) -> (0,2)
%  - (0,2) -> (1,0)

BLOCK_SIZE = 32;

M = [0 : 255]; 	  %! MEM<> [0,4]

A = zeros(1, BLOCK_SIZE); %! RFILE<> [0,2]

A = M(1:BLOCK_SIZE);

A = A + A; %! DPU[0,2]

M1 = zeros(1, 256); %! MEM<> [0,0]

M1(1:BLOCK_SIZE) = A;
