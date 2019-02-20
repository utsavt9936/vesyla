%VESYLA code for DBLSTM implementation 

COMPUTING_DRRA_ROW = 2;
COMPUTING_DRRA_COL = 4;
HIDDEN_SIZE = 320;             %No of columns in the hidden layer matrix    
SEQENCE_LEN =100;             %No of sequences (no of rows in input data)
NUM_LAYER = 4;                %No of LSTM layers in the DBLSTM network 
INPUT_SIZE = 120;             %No of elements in one sequence (no of columns in the input data)
OUTPUT_SIZE = 46;              %No of columns in the final output after softmax layer
REG_DEPTH = 32;               %size of a registerfile (each is 16 bit)

CONCAT_SIZE_1 = INPUT_SIZE + HIDDEN_SIZE + HIDDEN_SIZE + 8;
CONCAT_SIZE_2 = INPUT_SIZE + HIDDEN_SIZE + 8;


%% Eq.[2]
%% Original       : O = sigmoid(X * Wo + Bo)
%% Implementation : B = sigmoid(X * W  + B )

X_sram = ones(1, CONCAT_SIZE_1);   %! MEM [0,0]
W0_sram = ones(1, CONCAT_SIZE_1);  %! MEM [0,1]
W1_sram = ones(1, CONCAT_SIZE_1);  %! MEM [0,2]
B_sram = ones(1, HIDDEN_SIZE);     %! MEM [0,3]
X_reg_00 = zeros(1, REG_DEPTH/2);  %! RFILE [0,0]
X_reg_01 = zeros(1, REG_DEPTH/2);  %! RFILE [0,1]
X_reg_02 = zeros(1, REG_DEPTH/2);  %! RFILE [0,2]
X_reg_03 = zeros(1, REG_DEPTH/2);  %! RFILE [0,3]
X_reg_10 = zeros(1, REG_DEPTH/2);  %! RFILE [1,0]
X_reg_11 = zeros(1, REG_DEPTH/2);  %! RFILE [1,1]
X_reg_12 = zeros(1, REG_DEPTH/2);  %! RFILE [1,2]
X_reg_13 = zeros(1, REG_DEPTH/2);  %! RFILE [1,3]
W_reg_00 = zeros(1, REG_DEPTH/2);  %! RFILE [0,0]
W_reg_01 = zeros(1, REG_DEPTH/2);  %! RFILE [0,1]
W_reg_02 = zeros(1, REG_DEPTH/2);  %! RFILE [0,2]
W_reg_03 = zeros(1, REG_DEPTH/2);  %! RFILE [0,3]
W_reg_10 = zeros(1, REG_DEPTH/2);  %! RFILE [1,0]
W_reg_11 = zeros(1, REG_DEPTH/2);  %! RFILE [1,1]
W_reg_12 = zeros(1, REG_DEPTH/2);  %! RFILE [1,2]
W_reg_13 = zeros(1, REG_DEPTH/2);  %! RFILE [1,3]
B_reg_0  = zeros(1, REG_DEPTH);    %! RFILE [0,4]
B_reg_1  = zeros(1, REG_DEPTH);    %! RFILE [1,4]

for i = 1 : HIDDEN_SIZE/REG_DEPTH/2
	B_reg_0 = B_sram(i*(2*REG_DEPTH)-(2*REG_DEPTH)+1:i*(2*REG_DEPTH)-1*REG_DEPTH);
	B_reg_1 = B_sram(i*(2*REG_DEPTH)-(1*REG_DEPTH)+1:i*(2*REG_DEPTH)-0*REG_DEPTH);
	for j = 1 : REG_DEPTH
		for k = 1 : CONCAT_SIZE_1/COMPUTING_DRRA_COL/COMPUTING_DRRA_ROW/REG_DEPTH
			X_reg_00 = X_sram(REG_DEPTH/2*0+1:REG_DEPTH/2*1);
			X_reg_01 = X_sram(REG_DEPTH/2*1+1:REG_DEPTH/2*2);
			X_reg_02 = X_sram(REG_DEPTH/2*2+1:REG_DEPTH/2*3);
			X_reg_03 = X_sram(REG_DEPTH/2*3+1:REG_DEPTH/2*4);
			X_reg_10 = X_sram(REG_DEPTH/2*0+1:REG_DEPTH/2*1);
			X_reg_11 = X_sram(REG_DEPTH/2*1+1:REG_DEPTH/2*2);
			X_reg_12 = X_sram(REG_DEPTH/2*2+1:REG_DEPTH/2*3);
			X_reg_13 = X_sram(REG_DEPTH/2*3+1:REG_DEPTH/2*4);
			W_reg_00 = W0_sram(REG_DEPTH/2*0+1:REG_DEPTH/2*1);
			W_reg_01 = W0_sram(REG_DEPTH/2*1+1:REG_DEPTH/2*2);
			W_reg_02 = W0_sram(REG_DEPTH/2*2+1:REG_DEPTH/2*3);
			W_reg_03 = W0_sram(REG_DEPTH/2*3+1:REG_DEPTH/2*4);
			W_reg_10 = W1_sram(REG_DEPTH/2*0+1:REG_DEPTH/2*1);
			W_reg_11 = W1_sram(REG_DEPTH/2*1+1:REG_DEPTH/2*2);
			W_reg_12 = W1_sram(REG_DEPTH/2*2+1:REG_DEPTH/2*3);
			W_reg_13 = W1_sram(REG_DEPTH/2*3+1:REG_DEPTH/2*4);
			W_reg_00(1) = sum(X_reg_00 .* W_reg_00); %! DPU [0,0]
			W_reg_01(1) = sum(X_reg_01 .* W_reg_01); %! DPU [0,1]
			W_reg_02(1) = sum(X_reg_02 .* W_reg_02); %! DPU [0,2]
			W_reg_03(1) = sum(X_reg_03 .* W_reg_03); %! DPU [0,3]
			W_reg_10(1) = sum(X_reg_10 .* W_reg_10); %! DPU [1,0]
			W_reg_11(1) = sum(X_reg_11 .* W_reg_11); %! DPU [1,1]
			W_reg_12(1) = sum(X_reg_12 .* W_reg_12); %! DPU [1,2]
			W_reg_13(1) = sum(X_reg_13 .* W_reg_13); %! DPU [1,3]
			W_reg_01(1) = W_reg_01(1) + W_reg_00(1); %! DPU [0,1]
			W_reg_11(1) = W_reg_11(1) + W_reg_10(1); %! DPU [1,1]
			W_reg_02(1) = W_reg_02(1) + W_reg_01(1); %! DPU [0,2]
			W_reg_12(1) = W_reg_12(1) + W_reg_11(1); %! DPU [1,2]
			W_reg_03(1) = W_reg_03(1) + W_reg_02(1); %! DPU [0,3]
			W_reg_13(1) = W_reg_13(1) + W_reg_12(1); %! DPU [1,3]
			B_reg_0(j) = B_reg_0(j) + W_reg_03(1);   %! DPU [0,3]
			B_reg_1(j) = B_reg_1(j) + W_reg_13(1);   %! DPU [1,3]
		end
	end
	B_reg_0 = __sl_sigmoid(B_reg_0);               %! DPU [0,3]
	B_reg_1 = __sl_sigmoid(B_reg_1);               %! DPU [1,3]
	B_sram(i*(2*REG_DEPTH)-(2*REG_DEPTH)+1:i*(2*REG_DEPTH)-1*REG_DEPTH) = B_reg_0;
	B_sram(i*(2*REG_DEPTH)-(1*REG_DEPTH)+1:i*(2*REG_DEPTH)-0*REG_DEPTH) = B_reg_1;
end

