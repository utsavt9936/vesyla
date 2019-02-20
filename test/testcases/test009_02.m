
% Constants testcase

% Features:
%  - Utilizing constants in arithmetic statements

REGFILE_SIZE = 32;
B_RANGE = 11;
E_RANGE = 24;

A = [0  : REGFILE_SIZE-1]; 	%! RFILE<> [0,0]
B = [45 : 14]; 	  			%! RFILE<> [0,1]
C = zeros(1, REGFILE_SIZE); %! RFILE<> [1,0]

C(B_RANGE:E_RANGE) = A(B_RANGE:E_RANGE) + B(B_RANGE:E_RANGE); %! DPU [0,0]
