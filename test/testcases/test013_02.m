
% loop statement testcase (static)

% Features:
%  - Index calculation in the variable indexing

A = zeros(1, 9); %! RFILE<> [0,0]

for i = 1 : 8
	A(i + 1) = A(i) + 1; %! DPU [0,0]
end
