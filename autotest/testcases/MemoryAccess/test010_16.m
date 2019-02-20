
% Memory testcase

% Features:
%  - Memory Write
%  - Increasing distance between SRAM and Register File
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

M = zeros(1, 64); %! MEM<> [0,0]
B = [0 : 31];     %! RFILE<> [0,2]

M(1:32) = B;
