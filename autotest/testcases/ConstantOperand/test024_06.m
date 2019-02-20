
% Constant operation testcase

% Features:
%  - Load constant vector operation

result = fi(zeros(1,4), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,2]

result = fi(0.3, 1, 8, 7, 'RoundingMethod', 'Floor'); %! DPU [0,0]
