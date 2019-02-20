
% Parallelization testcase

% Features:
%  - Parallelization with reduction
%  - Final result register file and DPU location are different.

A = [0:31]; %! RFILE<> [0,1:2]
B = [12:43]; %! RFILE<> [1,1:2]
C = zeros(1, 32); %! RFILE<> [0:1,0]
E = zeros(1, 3); %! RFILE<> [0,1]
F = zeros(1, 1); %! RFILE<> [1,1]

C = A + B; %! DPU[0,1:2]

for i = 1 : 16
	E(1) = E(1) + C(i); %! DPU[0,0]
	E(2) = E(2) + C(i+16); %! DPU[1,0]
end

E(3) = E(2) + E(1); %! DPU[1,1]
