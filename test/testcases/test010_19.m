
% Memory testcase

% Features:
%  - Memory Write
%  - Writing to memory from more than one register file
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

M = zeros(1, 64); %! MEM<> [0,0]
B = [0 : 31];     %! RFILE<> [0,0]
C = [32: 63];     %! RFILE<> [0,1]

M( 1:32) = B;
M(33:64) = C;
