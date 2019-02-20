
% Memory testcase

% Features:
%  - Memory Write
%  - Writing one block of SRAM
%  - SRAM and Register File are in the same column.
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

M = zeros(1, 64); %! MEM<> [0,0]
B = [0 : 31];     %! RFILE<> [0,0]

M(1:16) = B(1:16);
