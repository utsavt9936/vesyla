
% if-statement inside loop

% Features:
%  - if-statement inside loops
%  - Using loop index within the if-statement body

A = [0:10]; %! RFILE<> [0,0]
B = [5:15]; %! RFILE<> [0,0]
C = zeros(1, 5); %! RFILE<> [0,0]

for i = 1 : 5
	if A(i) == B(1) %! DPU[0,0]
		C(i) = B(i) + A(2); %! DPU [0,0]
	else
		C(i) = B(i) + A(1); %! DPU [0,0]
	end
end

