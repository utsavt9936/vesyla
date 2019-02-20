
% loop statement testcase (dynamic)

% Features:
%  - Two level nested loops with an extra inner statement

A = [0 :11]; %! RFILE<> [0,0]
B = [20:34]; %! RFILE<> [1,0]
C = [2 :24]; %! RFILE<> [1,1]
D = [0 : 5]; %! RFILE<> [1,1]
E = [10:20]; %! RFILE<> [0,1]

for i = 1 : 6

	E(i+1) = A(i+2) + B(2*i); %! DPU [0,1]
	
	for j = 2 : 2 : 6
		A(i+j) = B(2*j+1) + C(i); %! DPU [0,0]
		D(j) = A(i+j) + D(i); %! DPU [1,1]
  	end
end
