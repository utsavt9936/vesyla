% Eq.[6]
% Original       : H = O + tanh(C)
% Implementation : O = O + tanh(C)

COMPUTING_DRRA_ROW = 2;
COMPUTING_DRRA_COL = 1;
HIDDEN_SIZE = 320;
REG_DEPTH = 32;

C_sram = ones(1, HIDDEN_SIZE);    %! MEM [0,0]
O_sram = ones(1, HIDDEN_SIZE);    %! MEM [0,0]

C_reg_0 = zeros(1, REG_DEPTH);  %! RFILE [0,0]
O_reg_0 = zeros(1, REG_DEPTH);  %! RFILE [1,0]

for i = 1 : HIDDEN_SIZE/(REG_DEPTH)/COMPUTING_DRRA_COL
	C_reg_0 = C_sram(i*REG_DEPTH*COMPUTING_DRRA_COL-REG_DEPTH*1+1:i*REG_DEPTH*COMPUTING_DRRA_COL-0*REG_DEPTH);
	O_reg_0 = O_sram(i*REG_DEPTH*COMPUTING_DRRA_COL-REG_DEPTH*1+1:i*REG_DEPTH*COMPUTING_DRRA_COL-0*REG_DEPTH);
	C_reg_0 = __sl_tanh(C_reg_0); %! DPU [0,0]
	O_reg_0 = O_reg_0 + C_reg_0;  %! DPU [0,0]
	O_sram(i*REG_DEPTH*COMPUTING_DRRA_COL-REG_DEPTH*1+1:i*REG_DEPTH*COMPUTING_DRRA_COL-0*REG_DEPTH) = O_reg_0;
end
