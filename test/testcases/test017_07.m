
% Calculation with accumulation testcase

% Features:
%  - Calculation using Preserving-MAC operation
%  - Utilizing integer values

A      = [1 : 32]; %! RFILE<> [0,0]
B      = [35 : 4]; %! RFILE<> [0,1]
result = [0];      %! RFILE<> [0,2]

for k = 1 : 3
	result = result + sum(A .* B); %! DPU [0,0]
end
