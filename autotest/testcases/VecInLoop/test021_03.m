
% Vector operation inside loop

% Features:
%  - Vector register transfer inside a loop

A = [0 :15]; %! RFILE <> [0,0]
B = [11:26]; %! RFILE<> [0,1]
C = zeros(1, 16); %! RFILE<> [1,0]
D = zeros(1, 16); %! RFILE<> [1,1]

for i = 0 : 3
	C(4*i+1 : 4*i+4) = A(4*i+1 : 4*i+4);
	D(4*i+1 : 4*i+4) = B(4*i+1 : 4*i+4);
end
