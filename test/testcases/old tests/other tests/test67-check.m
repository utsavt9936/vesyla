
% DPU Chaining
% An alternative to test66.m

A = [0  :15]; %! RFILE<> [1,0]
B = [11 :26]; %! RFILE<> [0,0]
C = zeros(1, 1); %! CDPU[0,0]

C(1) = A(2) + B(2);

B(1) = C(1) + A(5); %! DPU[1,0]
