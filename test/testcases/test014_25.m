
% loop statement testcase (dynamic)

% Features:
%  - Loops with a dynamic bound
%  - Using a different index expression

A = zeros(1, 9); %! RFILE<> [0,0]

inp1 = [1:4]; %! RFILE<> [0,0]
inp2 = [1:4]; %! RFILE<> [0,1]
out = zeros(1, 10); %! RFILE<> [1,0]

for i = 1 : 3
	for j = 1 : i
		out(3*(i-1)+j) = inp1(j) + inp2(i); %! DPU[0,1]
	end
end
