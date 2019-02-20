
% Constants testcase

% Features:
%  - Constant calculation

CVALUE = 10;
IDX = 4;

A = [CVALUE+10]; 	  %! RFILE<> [0,0]
B = [1 : 2*CVALUE+1]; %! RFILE<> [0,0]
C = zeros(1, 1); 	  %! RFILE<> [0,0]

C(1) = B(2*IDX) + A(1); %! DPU [0,0]
