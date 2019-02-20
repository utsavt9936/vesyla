
% loop statement testcase (static)

% Features:
%  - Simple loop statement

A = zeros(1, 10); %! RFILE<> [0,0]
B = [1:10]; %! RFILE<> [0,0]

for i = 1 : 9
	B(1:10) = B(1:10) + 0; %! DPU [0,0]
	A(i+1) = B(i+1) + A(i+1); %! DPU [0,0]
end
