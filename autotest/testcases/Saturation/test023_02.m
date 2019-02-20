
% Saturation testcase

% Features:
%  - Showing results using DPUs for multiplication in saturation and normal mode

A = fi([0.7071 0.4072 0.5073 0.1074 0.2075 0.2076 0.8077 0.0708 0.5570 0.9807], 1, 16, 15, 'RoundingMethod', 'Floor'); 	 %! RFILE<> [0,0]
B = fi([0.1201 0.1201 -0.1201 -0.1201 0.1201 0.1201 0.1201 0.1201 0.1201 0.1201], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,0]
C = fi(zeros(1, 10), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [1,0]
D = fi(zeros(1, 10), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [1,0]

C = A .* B; %! DPU<sat> [0,0]
D = A .* B; %! DPU [1,0]
