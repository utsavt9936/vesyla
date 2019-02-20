
% Memory testcase

% Features:
%  - Memory Write
%  - Writing to memory from more than one register file
%  - Unconsecutive writes
%  - Note that for memory write instructions, sv_results4_srm_x.txt should be checked.

% (This testcase has problem -> conflict of route instructions,
%  A naiive solution is to add extra delay between them.
%  For example in scheduleStartClkforSram add "prevMaxClk_+= 2;" prior to the for loop)

M = zeros(1, 64); %! MEM<> [0,0]
B = [0 : 31];     %! RFILE<> [0,0]
C = [32: 63];     %! RFILE<> [0,1]

M( 1:16) = B(1:16);
M(33:64) = C;
M(17:32) = B(17:32);
