
% Memory testcase

% Features:
%  - Memory Write
%  - Writing to more than one memory
%  - SRAM and Register Files are in the same column.
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

M1 = zeros(1, 64); %! MEM<> [0,0]
M2 = zeros(1, 64); %! MEM<> [0,1]

B = [0 : 31];     %! RFILE<> [0,0]
C = [32: 63];     %! RFILE<> [0,1]

M1(1:32) = B;
M2(1:32) = C;
