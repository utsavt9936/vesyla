
% Constants testcase

% Features:
%  - Utilizing constants in initialization

REGFILE_SIZE = 32;

A = [0  : REGFILE_SIZE-1]; 	%! RFILE<> [0,0]
B = [45 :-1: 14]; 	  			%! RFILE<> [0,1]
C = zeros(1, REGFILE_SIZE); %! RFILE<> [1,0]

C = A + B; %! DPU [0,0]
