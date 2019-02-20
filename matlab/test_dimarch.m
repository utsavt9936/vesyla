var_mem = ones(1, 64);  %! MEM [0,0]
var1_reg = zeros(1, 32); %! RFILE [0,0]
var2_reg = zeros(1, 32); %! RFILE [0,0]

var1_reg = var_mem(1:32);
var2_reg = var_mem(33:64);
