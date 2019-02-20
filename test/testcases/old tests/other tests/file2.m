

% for RFILE distribution use <> or <even_dist> or <full_dist> or <custom_dist>
% <> is equal to <even_dist>

% Determining constants by 'row', 'col', 'dimension', and 'parallelism' keywords

% for statement pragma: use 'parallel' for parallel loops, otherwise they run sequentially
% if statement pragma: use 'structural' for structural if statments, otherwise they considered as conditional if statements

r=0; %! row
c= 1; %! col

N=20;   %! dimension
M=4;    %! parallelism % Number of DPUs/Streams
P=N/M;  % restricted to cases where N is integer multiple of M

x = zeros (P,M);  %! RFILE<full_dist> [r, c:c+M-1]
c = zeros (P,M);  %! RFILE<> [r+1, c:c+M-1]


% [P, M] = size (x);
l = zeros(M,1); %! MEM [r, c:c+M-1]

for j = M:-1:1 %! parallel

	l(j) = sum (x(:, j).*c(:, j)); %! DPU [r, c:c+M-1]
	%x(2:P,j) = x(1:P-1,j);  % AGU in circular buffer mode 

	if j==1 %! structural
		x(1, j) = xn; % new sample in first register file 
	else
		x(1, j) = x(P, j-1); % moving data from (j-1)th refi to jth refi 
	end

end

res = sum(l) %! DPU [r, c:c+M-1]
