
% Memory testcase

% Features:
%  - Memory Read
%  - Reading from memory to more than one register file

M = [0 : 63]; 	  %! MEM<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,0]
C = zeros(1, 32); %! RFILE<> [0,1]
X = zeros(1, 32); %! RFILE<> [1,0]

B = M(1:32);
C = M(33:64);

X = B + C; %! DPU[0,0]
