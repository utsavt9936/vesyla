
% Vector operation inside loop

% Features:
%  - Vector memory transfer inside a loop

A = [0 :31]; %! MEM<> [0,0]
C = zeros(1, 32); %! RFILE<> [0,0]
D = zeros(1, 32); %! RFILE<> [0,1]

for i = 0 : 1
	C(16*i+1 : 16*i+16) = A(16*i+1 : 16*i+16);
end

D = C;
