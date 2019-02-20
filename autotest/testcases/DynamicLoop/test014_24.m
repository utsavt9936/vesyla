
% loop statement testcase (dynamic)

% Features:
%  - Loops with a dynamic bound
%  - Using index of the dynamic-bound loop inside the loop body

A = zeros(1, 9); %! RFILE<> [0,0]

inp1 = [1:4]; %! RFILE<> [0,0]
inp2 = [1:4]; %! RFILE<> [0,1]
out = zeros(1, 10); %! RFILE<> [1,0]

for i = 1 : 3
	for j = 1 : i + 1
		out(3 * i) = inp1(j) + inp2(i+1); %! DPU[0,1]
	end
end
