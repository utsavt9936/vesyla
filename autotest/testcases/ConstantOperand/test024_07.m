
% Constant operation testcase

% Features:
%  - Add with a constant scalar integer operation

A      = [1:15]; %! RFILE<> [0,0]
result = zeros(1,4); %! RFILE<> [0,2]

result(1) = A(3) + 2; %! DPU [0,0]
