
% if-statement testcase

% Features:
%  - Having more than one statement inside the body

A = [0 :10]; %! RFILE<> [0,0]
B = zeros(1, 6); %! RFILE<> [0,0]

if A(2) == B(1)
	B(1) = B(1) + A(2); %! DPU [0,0]
	B(2) = B(1) + A(2); %! DPU [0,0]
else
	B(3) = B(2) + A(3); %! DPU [0,0]
end

if A(1) == B(1)
	B(4) = B(1) + A(2); %! DPU [0,0]
	B(5) = B(1) + A(2); %! DPU [0,0]
else
	B(6) = B(2) + A(3); %! DPU [0,0]
end
