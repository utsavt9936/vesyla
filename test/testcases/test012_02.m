
% if-statement testcase

% Features:
%  - Simple if-then-else statement

A = [0 :10]; %! RFILE<> [0,0]
B = zeros(1, 5); %! RFILE<> [0,0]

if A(2) == B(1) %! DPU[0,0]
	B(1) = B(1) + A(2); %! DPU [0,0]
else
	B(2) = B(2) + A(3); %! DPU [0,0]
end

if A(1) == B(1) %! DPU[0,0]
	B(3) = B(1) + A(2); %! DPU [0,0]
else
	B(4) = B(2) + A(3); %! DPU [0,0]
end
