
% Memory testcase

% Features:
%  - Memory Write
%  - Modifying SRAM location
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

M = zeros(1, 64); %! MEM<> [0,2]
B = [0 : 31];     %! RFILE<> [0,0]

M(1:32) = B;
