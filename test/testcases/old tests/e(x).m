
% e(x) Taylor series

N = 8;

column = 1; %! range
row = 1; %! range

load('x.mat','x'); %! RFILE[row,column]; address_range

load('fact_x.mat', 'fact_x'); %! RFILE[row, column+1]; address_range

const_1 = 1; %! RFILE[row+1, column]

eX = 0; %! RFILE[row+1, column]

term = 0; %! DPU[row, column+1]

for i = 1 : N
	x(i+1) = x(i) .* x(1); %! DPU[row, column]
	term = sum(x(i) .* fact_x(i));
end

eX = term + const_1; %! DPU[row, column]
