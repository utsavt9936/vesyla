
% sin(x) Taylor series - partially parallel

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
Sum = zeros(M,1); %! DPU[row+1, column_range]
index = 1;
j = 1;

x(N) = x(1) .* x(1); %! DPU[row, column]

for i = 1 : N
	x(i+1) = x(i) .* x(N); %! DPU[row, column]
	term(1,j) = x(i) .* fact_x(i); %! DPU[row, column+1]

	if index == par
		j = j + 1;
		index = 1;
	else
		index = index + 1;
	end
end

for i = 1 : 2 : ceil(N/M)
	for j = 1 : M
		Diff(j) = term(i,j) - term(i+1, j);
		Sum(j) = sum(Diff(:,j));
	end
end

sinX = sum(Sum); %! DPU[row, column]; adder_tree

