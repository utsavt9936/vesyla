
% Vector operation inside a loop
% memory transfer

A = [0 :31]; %! MEM<> [0,0]
B = [11:42]; %! MEM<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]
D = zeros(1, 32); %! RFILE<> [1,1]

for i = 0 : 1
	C(16*i+1 : 16*i+16) = A(16*i+1 : 16*i+16);
	D(16*i+1 : 16*i+16) = B(16*i+1 : 16*i+16);
end
