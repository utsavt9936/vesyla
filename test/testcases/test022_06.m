
% Parallelization testcase

% Features:
%  - Having multiple parallelization operations on the same DPUs

A = [0:31]; %! RFILE<> [0,1:2]
B = [12:43]; %! RFILE<> [1,1:2]
C = zeros(1, 32); %! RFILE<> [0:1,0]
D = zeros(1, 32); %! RFILE<> [0:1,0]

C = A + B; %! DPU[0:1,0]
D = A .* B; %! DPU[0:1,0]
