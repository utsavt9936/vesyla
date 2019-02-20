% Memory testcase

% Features:
%  - Memory Read
%  - Reading two block of SRAM
%  - SRAM and Register File are in different columns.
%  - (1,4) -> (0,2)

M = [0 : 63]; 	  %! MEM<> [0,4]
B = zeros(1, 32); %! RFILE<> [0,2]
X = zeros(1, 32); %! RFILE<> [1,0]

B(1:32) = M(1:32);

X = B + B; %! DPU[0,0]
