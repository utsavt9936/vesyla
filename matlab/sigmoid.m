A = [-128 127 0 -64 64 65]; %! RFILE [0,0]
B = zeros(1, 6); %! RFILE [0,0]
C = zeros(1, 6); %! RFILE [0,0]

B = __sl_sigmoid(A); %! DPU [0,0]
C = __sl_tanh(A); %! DPU [0,0]
