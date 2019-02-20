
% Vector integer operation testcase

% Features:
%  - Using multiplication

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C = A .* B; %! DPU [0,0]
