
% if-statement inside loop

% Features:
%  - if-statement inside loop

A = [0:10]; %! RFILE<> [0,0]
B = [5:15]; %! RFILE<> [0,0]
C = zeros(1, 5); %! RFILE<> [0,0]

for i = 1 : 5
	if A(i) == B(1) %! DPU[0,0]
		C(1) = B(1) + A(2); %! DPU [0,0]
	else
		C(1) = B(1) + A(1); %! DPU [0,0]
	end
end

