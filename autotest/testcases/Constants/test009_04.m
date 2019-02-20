
% Constants testcase

% Features:
%  - Utilizing constants in loop body
%  - Constant calculation

REGFILE_SIZE = 32;
ITER_NO = 32;
OFFSET = 5;

A = [0  : REGFILE_SIZE-1]; 	%! RFILE<> [0,0]
B = [45 : 14]; 	  			%! RFILE<> [0,1]
C = zeros(1, REGFILE_SIZE); %! RFILE<> [1,0]

for i = 1 : ITER_NO-OFFSET
	C(i+OFFSET) = A(i+OFFSET) + B(i+OFFSET); %! DPU [0,0]
end
