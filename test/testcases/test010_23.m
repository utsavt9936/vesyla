
% Memory testcase

% Features:
%  - Memory Read
%  - Multiple unconsecutive read from memory to the same register file

%(The problem is related to an incorrect initial delay in a REFI instruction. It should be 4 instead of 3)

M = [0 : 63]; 	  %! MEM<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,0]
X = zeros(1, 32); %! RFILE<> [1,0]

B(1:16) = M(1:16);

X = B + B; %! DPU[0,0]

B(17:32) = M(17:32);

X = B + B; %! DPU[0,0]
