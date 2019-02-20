
% Vector integer operation testcase

% Features:
%  - Using vector operations on vectors with a name and vectors with a range

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 10); %! RFILE<> [1,0]
D = zeros(1, 10); %! RFILE<> [1,1]

C = A(1:10) + B(1:10); %! DPU [0,0]
D = C + A(11:20); %! DPU [0,1]
