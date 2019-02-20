
% Vector integer operation testcase

% Features:
%  - More than one vector operations writing to the same variable

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C( 1:10) = A(10:19) + B(10:19); %! DPU [0,0]
C(11:16) = A( 6:11) + B(22:27); %! DPU [0,0]
