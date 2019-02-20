
%**<<CURRENTLY UNSUPPORTED>>**

% Vector integer operation testcase

% Features:
%  - Using negative increment

A = [0  : 31]; 	  %! RFILE<> [0,0]
B = [45 : 14]; 	  %! RFILE<> [0,1]
C = zeros(1, 32); %! RFILE<> [1,0]

C(32:-1:1) = A(1:32) + B(1:32); %! DPU [0,0]

