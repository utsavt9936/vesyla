
% loop statement testcase (dynamic)

% Features:
%  - Using address function inside loops
%  - Address function is outside the inner loop.

A = [0 :11]; %! RFILE<> [0,0]
B = [20:39]; %! RFILE<> [0,0]
C = [2 :24]; %! RFILE<> [1,1]
D = [0 : 5]; %! RFILE<> [1,1]

for i = 1 : 6

	addr = 2 * i + 1;

	for j = 2 : 2 : 6
		A(i+j) = B(addr) + C(i); %! DPU [0,0]
		D(j) = A(i+j) + D(i); %! DPU [1,1]
  	end
end
