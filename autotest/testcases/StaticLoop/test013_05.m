
% loop statement testcase (static)

% Features:
%  - Loop boundary with an increment bigger than one

A = [0 :11]; %! RFILE<> [0,0]
B = [20:34]; %! RFILE<> [0,0]
C = [2 :24]; %! RFILE<> [1,1]
D = [0 : 5]; %! RFILE<> [1,1]

k = 0+5; %!RACCU_VAR
for j = 2 : 2 : 6

	A(j) = B(k) + C(j); %! DPU [0,0]
	D(j) = A(j) + D(j); %! DPU [1,1]
	k=k+4;
end
