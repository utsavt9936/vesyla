
% Vector integer operation testcase

% Features:
%  - Using increments bigger than 1

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C(1:2:31) = A(1:2:31) + B(2:2:32); %! DPU [0,0]
C(2:2:32) = A(2:2:32) + B(1:2:31); %! DPU [0,0]

