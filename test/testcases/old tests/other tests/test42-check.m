
% memory - data in STILE
% Note that in memory row=0 is for CONTILEs and row=1...N are for STILEs.


A = [0 :15]; %! MEM <> [1,0]
B = zeros(1, 17); %! RFILE<> [0,0]
C = [10:25]; %! MEM <> [1,1]

B(1:16) = A(1:16);

B(17) = B(5) + B(2); %! DPU[0,0]
