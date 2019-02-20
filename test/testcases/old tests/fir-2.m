
% FIR

M = [1 2 4]; %! parallelism
N = 96;
S = N / (2 * M); % splitting value
T = 4; % number of allocated RegFiles
r = 0;
c = 0;

x = zeros(1, N); %! RFILE<even> [r, c:c+T-1] [r, [c c+3 c+1 c+2]]
coeff = zeros(1, N/2); %! RFILE<even> [r+1, c:c+T/2-1]
temp = zeros(1, M); %! CDPU<> [r,c:c+M-1]

2:24 <- 1:23


for i = 1 : M
	temp(i) = sum(coeff((i-1)*S+1 : i*S) .* (x((i-1)*S+1 : i*S) + x((2*M-i+1)*S : -1 : (2*M-i)*S+1)));

	x(2)

	out((row-1)*WIDTH + col) = acc(1);
end

