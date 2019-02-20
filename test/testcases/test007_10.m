
% Vector integer operation testcase

% Features:
%  - Using subtraction

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C = B - A; %! DPU [0,0]
