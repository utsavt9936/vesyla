% Memory testcase

% Features:
%  - Memory Write/Read
%  - Writing to memory and then reading from memory
%  - SRAM and Register File are in different columns (distance=1).
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.
%  - (0,1) -> (1,2)
%  - (1,2) -> (0,1)


BLOCK_SIZE = 32;


M = zeros(1, 256); %! MEM<> [0,2]

B = [0 : 31];     %! RFILE<> [0,1]

M(1:32) = B;

B = 0; %! DPU[0,1]

B = M(1:BLOCK_SIZE);
