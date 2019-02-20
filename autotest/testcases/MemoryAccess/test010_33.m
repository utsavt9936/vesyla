% Memory testcase

% Features:
%  - Memory Write
%  - Writing two blocks of SRAM
%  - SRAM and Register File are in different columns (distance=4).
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.
%  - (0,0) -> (1,4)

M = zeros(1, 64); %! MEM<> [0,4]
B = [0 : 31];     %! RFILE<> [0,0]

M(1:32) = B;
