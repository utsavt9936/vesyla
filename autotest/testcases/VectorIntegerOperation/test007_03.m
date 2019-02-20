
% Vector integer operation testcase

% Features:
%  - More than one vector operations with separate outputs

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]
D = zeros(1, 32); %! RFILE<> [1,1]

C = A + B; %! DPU [0,0]
D(10:15) = A(6:11) + B(21:(27-1)); %! DPU [0,1]
