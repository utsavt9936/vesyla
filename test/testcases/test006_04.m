
% Scalar integer operation testcase

% Features:
%  - Using negative values in calculations

A = [0 5 -2 -15 3 3]; %! RFILE<> [0,0]
B = [3 15 3 14 0 -2]; %! RFILE<> [0,1]
C = zeros(1, 6);	 %! RFILE<> [1,0]

C(1) = A(3) + B(3); %! DPU [0,0]
C(2) = A(4) + B(4); %! DPU [0,0]

C(3) = A(3) - B(3); %! DPU [0,0]
C(4) = A(4) - B(4); %! DPU [0,0]

C(5) = A(3) * B(3); %! DPU [0,0]
C(6) = A(4) * B(4); %! DPU [0,0]
