
% Initialization testcase

% Features:
%  - Vector initialization
%  - Single element initialization

A = [0:31]; %! RFILE<> [0,0]
B = [31:0]; %! RFILE<> [0,1]
C = [0];    %! RFILE<> [0,2]

C(1) = A(10) + B(10); %! DPU [0,0]
