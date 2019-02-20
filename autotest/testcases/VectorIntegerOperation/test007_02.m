
% Vector integer operation testcase

% Features:
%  - Using vector range

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C(10:15) = A(6:11) + B(22:27); %! DPU [0,0]
