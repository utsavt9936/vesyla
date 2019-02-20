
% Memory testcase

% Features:
%  - Memory Read
%  - Modifying Register File location

M = [0 : 63]; 	  %! MEM<> [0,2]
B = zeros(1, 32); %! RFILE<> [1,1]
X = zeros(1, 32); %! RFILE<> [1,0]

B = M(1:32);

X = B + B; %! DPU[0,0]
