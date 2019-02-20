
% Memory testcase

% Features:
%  - Memory Read
%  - Reading from memory within a loop

RFILE_SIZE = 32;

M = [0 : 255]; 	  %! MEM<> [0,0]
B = zeros(1, RFILE_SIZE); %! RFILE<> [0,0]
X = zeros(1, RFILE_SIZE); %! RFILE<> [1,0]

for k = 1 : 4
	B = M((k-1)*RFILE_SIZE+1 : k*RFILE_SIZE);
	X = X + B; %! DPU[0,0]
end
