
% loop statement testcase (static)

% Features:
%  - Several index calculation in the variable indexing

A = [0 :10]; %! RFILE<> [0,0]
B = [20:34]; %! RFILE<> [0,0]
C = [2 :24]; %! RFILE<> [1,1]
D = [0 : 5]; %! RFILE<> [1,1]

for i = 1 : 6
  A(i+2) = B(2*i+1) + C(1); %! DPU [0,0]
  D(i) = A(i+2) + D(i); %! DPU [1,1]
end
