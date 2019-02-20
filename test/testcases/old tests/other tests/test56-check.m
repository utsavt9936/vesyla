
% Parallelization

A = [0:31]; %! RFILE<even> [0,1:2]
B = [2 4 6 8 2 4 6 8 2 4 6 8 2 4 6 8]; %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<even> [1,1:2]
D = zeros(1, 32); %! RFILE<even> [1,2:3]
E = zeros(1, 1); %! RFILE[1,0]

C = A + B; %! DPU[0,0:1]

for i = 1 : 32
	E(1) = E(1) + C(i); %! DPU[1,0]
end

for i = 0 : 1 %! parallel
	D = A + B; %! DPU[0, i]
end

for i = 0 : 1 %! parallel
	idx = 16 * i + 1;
	D(idx:idx+15) = A(idx:idx+15) + B(1:16); %! DPU[0, i]
end
