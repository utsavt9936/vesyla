
% Vector integer operation testcase

% Features:
%  - Using the same variable as the operands of a vector operation

A = [0  : 31]; 	  %! RFILE<> [0,0]
C = zeros(1, 32); %! RFILE<> [1,0]

C = A + A; %! DPU [0,0]
