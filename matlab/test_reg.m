var_reg_0 = ones(1,32); %! RFILE [0,0]
var_reg_1 = ones(1,32); %! RFILE [0,1]

var_reg_0 = var_reg_0 + var_reg_1; %! DPU [0,0]
