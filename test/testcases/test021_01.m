
% Vector operation inside loop

% Features:
%  - MAC operation inside a loop

A = [0 :15]; %! RFILE <> [0,0]
B = [11:26]; %! RFILE<> [0,1]
C = zeros(1, 5); %! RFILE<> [1,0]

for i = 1 : 5
	C(i) = sum(A .* B); %! DPU[0,0]
end
