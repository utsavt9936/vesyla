
% Memory testcase

% Features:
%  - Memory Read
%  - Reading from memory to multiple cells within a nested loop

RFILE_SIZE = 32;

M1 = [0 : 255]; 	  %! MEM<> [0,0]
M2 = [0 : 255]; 	  %! MEM<> [0,1]
B1 = zeros(1, RFILE_SIZE); %! RFILE<> [0,0]
B2 = zeros(1, RFILE_SIZE); %! RFILE<> [0,1]
X = zeros(1, RFILE_SIZE); %! RFILE<> [1,0]

for i = 1 : 3
	for k = 1 : 4
		B1 = M1((k-1)*RFILE_SIZE+1 : k*RFILE_SIZE);
		B2 = M2((k-1)*RFILE_SIZE+1 : k*RFILE_SIZE);
		
		X = X + B1; %! DPU[0,0]
		X = X + B2; %! DPU[0,0]
	end
end
