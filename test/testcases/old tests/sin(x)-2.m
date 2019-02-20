
% sin(x) Taylor series - fully parallel

N = 8;
M = 2;
par = ceil(N / M);
row = 1;
column_range = (1:M); %! range
column = 1;
address_range = (1:N); %! range

load('x.mat','x'); %! RFILE[row,column]; address_range

load('fact_x.mat', 'fact_x'); %! RFILE[row, column+1]; address_range

load('term.mat', 'term'); %! RFILE[row+1, column_range]; address_range

term = reshape(term, par, M);

sinX = 0; %! RFILE[row+1, M+1]; address_range

Diff = zeros(M,1); %! DPU[row, column_range]

x(N) = x(1) .* x(1); %! DPU[row, column]

for i = 1 : N
	x(i+1) = x(i) .* x(N); %! DPU[row, column]
	term(1,i) = x(i) .* fact_x(i); %! DPU[row, column+1]
end

for i = 1 : 2 : N
	Diff(i) = term(1,i) - term(1, j+1);
end

sinX = sum(Diff); %! adder_tree

