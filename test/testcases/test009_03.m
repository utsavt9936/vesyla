
% Constants testcase

% Features:
%  - Utilizing constants in loop boundary

REGFILE_SIZE = 32;
ITER_NO = 32;

A = [0  : REGFILE_SIZE-1]; 	%! RFILE<> [0,0]
B = [45 :-1: 14]; 	  			%! RFILE<> [0,1]
C = zeros(1, REGFILE_SIZE); %! RFILE<> [1,0]

for i = 1 : ITER_NO
	C(i) = A(i) + B(i); %! DPU [0,0]
end
