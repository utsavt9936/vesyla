
% Scalar integer operation testcase

% Features:
%  - Multiplication

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C(1) = A(1) * B(1); %! DPU [0,0]
C(2) = A(1) .* B(1); %! DPU [0,0]
