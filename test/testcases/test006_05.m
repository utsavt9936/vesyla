
% Scalar integer operation testcase

% Features:
%  - Using the same variable for both operands of an arithmetic statement

A = [0  : 31]; 	  %! RFILE<> [0,0]
C = zeros(1, 32); %! RFILE<> [1,0]

C(1) = A(3) + A(18); %! DPU [0,0]
