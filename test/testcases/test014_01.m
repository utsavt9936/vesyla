
% loop statement testcase (dynamic)

% Features:
%  - Simple loop statement

A = zeros(1, 10); %! RFILE<> [0,0]
B = [1:10]; %! RFILE<> [0,0]

for i = 1 : 10
	A(i) = B(i) + A(i); %! DPU [0,0]
end
