
% Register transfer

% Features:
%  - Using register transfer to reach far cells

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = zeros(1, 32); %! RFILE<> [0,2]
C = zeros(1, 32); %! RFILE<> [0,3]
D = zeros(1, 32); %! RFILE<> [0,4]

B = A;
C = B;

D = C + C %! DPU [0,4]

