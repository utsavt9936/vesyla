
% Memory testcase

% Features:
%  - Memory Read
%  - Reading from memory to more than one register file
%  - Unconsecutive reads

M = [0 : 63]; 	  %! MEM<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,0]
C = zeros(1, 32); %! RFILE<> [0,1]
X = zeros(1, 32); %! RFILE<> [1,0]

B(1:16) = M(1:16);
C = M(33:64);
B(17:32) = M(17:32);

X = B + C; %! DPU[0,0]
