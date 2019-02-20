M = ones(1, 64); %! MEM [0,0]
R1 = zeros(1, 64); %! RFILE [0,0]
R2 = ones(1, 64); %! RFILE [0,1]

R1 = M;

R2 = R1 + R2; %! DPU [0,0]
