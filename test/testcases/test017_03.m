
% Calculation with accumulation testcase

% Features:
%  - MAC operation inside loop

tf_1_4 = [0:31]; %! RFILE<> [0,0]
tf_5_8 = [0:31]; %! RFILE<> [0,1]

x_1_4 = [0:31]; %! RFILE<> [1,0]
x_5_8 = [0:31]; %! RFILE<> [1,1]

X_1_4 = [0:31]; %! RFILE<> [0,2]
X_5_8 = [0:31]; %! RFILE<> [1,2]

for row=1:4
	for i=1:4
		X_1_4((row-1)*8+i) = sum(x_1_4((row-1)*8+1:row*8) .* tf_1_4((i-1)*8+1:i*8)); %! DPU [0,0]
	end
end
