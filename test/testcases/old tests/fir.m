
% Asymmetric FIR Filter

N = 47;
M = 1;
par = N / M;
row = 1;
column_range = (1:M); %! range
address_range = (1:N); %! range

x(address_range) = zeros(par,M); %! RFILE[row, column_range]_A
x = reshape(x(1:par*M), par, M);

load('c.mat', 'c'); %! RFILE[row, column_range]_B; address_range
c = reshape(c(1:par*M), par, M);

load('samples.mat', 'new_sample'); %! RFILE[row+1, 1], address_range

res = 0; %! RFILE[row+1, M+1]

mac_out = zeros(M,1); %! DPU[row, column_range]

for i = 1 : N
	for j = 1 : M
		if j == 1
			x(1, j) = new_sample(i);
		end
		mac_out(j) = sum(x(:,j) .* c(:,j));
		x(2:P, j) = x(1: P-1, j);
	end
	res = sum(mac_out); %! adder_tree
end

