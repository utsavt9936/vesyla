
% Memory testcase

% Features:
%  - Memory Read
%  - Reading from more than one memory
%  - SRAM and Register Files are in different columns.

M1 = [0 : 63]; 	  %! MEM<> [0,0]
M2 = [0 : 63]; 	  %! MEM<> [0,1]

B = zeros(1, 32); %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [0,0]
X = zeros(1, 32); %! RFILE<> [1,0]

B = M1(1:32);
C = M2(1:32);

X = B + C; %! DPU[0,0]
