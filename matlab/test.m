%VESYLA code for DBLSTM implementation 

M00   = ones(1,64);   %! MEM   [0,0]
M01   = ones(1,64);   %! MEM   [0,0]
R0   = zeros(1,32);   %! RFILE [0,0]
R1   = zeros(1,32);   %! RFILE [0,1]
R2   = zeros(1,32);   %! RFILE [0,2]
R3   = zeros(1,32);   %! RFILE [0,3]

M1   = ones(1,128);   %! MEM   [0,1]
S0   = zeros(1,32);   %! RFILE [1,0]
S1   = zeros(1,32);   %! RFILE [1,1]
S2   = zeros(1,32);   %! RFILE [1,2]
S3   = zeros(1,32);   %! RFILE [1,3]


R0 = M00(32*0+1:32*1);
R1 = M00(32*1+1:32*2);
R2 = M01(32*0+1:32*1);
R3 = M01(32*1+1:32*2);
S0 = M1(32*0+1:32*1);
S1 = M1(32*1+1:32*2);
S2 = M1(32*2+1:32*3);
S3 = M1(32*3+1:32*4);
