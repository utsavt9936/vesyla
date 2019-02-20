%VESYLA code for DBLSTM implementation 

G=32;                       %DRRA(or no of silago blocks) group size
P=16;                       %Weight precision
hiddenSize=320;             %No of columns in the hidden layer matrix    
seqLength =100;             %No of sequences (no of rows in input data)
numLayers=4;                %No of LSTM layers in the DBLSTM network 
input_dim =120;             %No of elements in one sequence (no of columns in the input data)
output_dim=46;              %No of columns in the final output after softmax layer
reg_depth=64;               %size of a registerfile (each is 16 bit)
B= 16;                      %Bits per input element (per channel 16 bits in wav file)  
X= 15;                      %for fractional part
W= 768;                     %total elements in input vector for ft,it and ot
Z= 32;                      %for transferring 32 values after they get accumulated in full_multiplication register(320)
%SRAM declaration: store for one group

%weights_ping_dimarch  = [1 : W];   %! MEM [0,0]
input_ping_dimarch    = [1 : W];   %! MEM [0,0]
weights_ping_dimarch  = [1 : W];   %! MEM [0,1]
%weights_pong_dimarch  = [1 : W];   %! MEM [0,1]
bias_dimarch          = [1 : hiddenSize];   %! MEM [0,2]
full_mul_dimarch      = [1 : hiddenSize];   %! MEM [0,2]
%Registerfile declaration
input_reg_1       = zeros(1,reg_depth);  %! RFILE [0,0]
input_reg_2       = zeros(1,reg_depth);  %! RFILE [0,1]
input_reg_3       = zeros(1,reg_depth);  %! RFILE [0,2]
input_reg_4       = zeros(1,reg_depth);  %! RFILE [0,3]
input_reg_5       = zeros(1,reg_depth);  %! RFILE [0,4]
input_reg_6       = zeros(1,reg_depth);  %! RFILE [0,5]
input_reg_7       = zeros(1,reg_depth);  %! RFILE [0,6]
input_reg_8       = zeros(1,reg_depth);  %! RFILE [0,7]
input_reg_9       = zeros(1,reg_depth);  %! RFILE [0,8]
input_reg_10      = zeros(1,reg_depth);  %! RFILE [0,9]
input_reg_11      = zeros(1,reg_depth);  %! RFILE [0,10]
input_reg_12      = zeros(1,reg_depth);  %! RFILE [0,11]
weight_reg_1      = zeros(1,reg_depth);  %! RFILE [1,0]
weight_reg_2      = zeros(1,reg_depth);  %! RFILE [1,1]
weight_reg_3      = zeros(1,reg_depth);  %! RFILE [1,2]
weight_reg_4      = zeros(1,reg_depth);  %! RFILE [1,3]
weight_reg_5      = zeros(1,reg_depth);  %! RFILE [1,4]
weight_reg_6      = zeros(1,reg_depth);  %! RFILE [1,5]
weight_reg_7      = zeros(1,reg_depth);  %! RFILE [1,6]
weight_reg_8      = zeros(1,reg_depth);  %! RFILE [1,7]
weight_reg_9      = zeros(1,reg_depth);  %! RFILE [1,8]
weight_reg_10     = zeros(1,reg_depth);  %! RFILE [1,9]
weight_reg_11     = zeros(1,reg_depth);  %! RFILE [1,10]
weight_reg_12     = zeros(1,reg_depth);  %! RFILE [1,11]
full_mul_reg      = zeros(1,Z);          %! RFILE [0,12]
%pm_reg_2          = zeros(1,reg_depth);  %! RFILE [7,0]
%pm_reg_3          = zeros(1,reg_depth);  %! RFILE [8,0]
%pm_reg_4          = zeros(1,reg_depth);  %! RFILE [9,0]
%cell_state_reg    = zeros(1,reg_depth);  %! RFILE [10,0]
%DECLARE MORE PM_REG AND MORE WEIGHT REG
input_reg_1=input_ping_dimarch(1:64);
input_reg_2=input_ping_dimarch(65:128);
input_reg_3=input_ping_dimarch(129:192);
input_reg_4=input_ping_dimarch(193:256);
input_reg_5=input_ping_dimarch(257:320);
input_reg_6=input_ping_dimarch(321:384);
input_reg_7=input_ping_dimarch(385:448);
input_reg_8=input_ping_dimarch(449:512);
input_reg_9=input_ping_dimarch(513:576);
input_reg_10=input_ping_dimarch(577:640);
input_reg_11=input_ping_dimarch(641:704);
input_reg_12=input_ping_dimarch(705:768);
for sequencesweep= 1:320/Z

%load bias from DiMarch to RFILE
	full_mul_reg(1:Z)=bias_dimarch(sequencesweep*Z-Z+1:sequencesweep*Z); 
  for resultsweep=1:Z        %for transferring 32 values after they get accumulated in full_multiplication register
%  index = sequencesweep-1;
%  index = (index*32+resultsweep);
%%transfer data from DIMARCH to registerfiles
  weight_reg_1=weights_ping_dimarch(reg_depth*0+1:reg_depth*1);
  weight_reg_2=weights_ping_dimarch(reg_depth*1+1:reg_depth*2);
  weight_reg_3=weights_ping_dimarch(reg_depth*2+1:reg_depth*3);
  weight_reg_4=weights_ping_dimarch(reg_depth*3+1:reg_depth*4);
  weight_reg_5=weights_ping_dimarch(reg_depth*4+1:reg_depth*5);
  weight_reg_6=weights_ping_dimarch(reg_depth*5+1:reg_depth*6);
  weight_reg_7=weights_ping_dimarch(reg_depth*6+1:reg_depth*7);
  weight_reg_8=weights_ping_dimarch(reg_depth*7+1:reg_depth*8);
  weight_reg_9=weights_ping_dimarch(reg_depth*8+1:reg_depth*9);
  weight_reg_10=weights_ping_dimarch(reg_depth*9+1:reg_depth*10);
  weight_reg_11=weights_ping_dimarch(reg_depth*10+1:reg_depth*11);
  weight_reg_12=weights_ping_dimarch(reg_depth*11+1:reg_depth*12);
          weight_reg_1(1)    = sum(input_reg_1.* weight_reg_1);    %! DPU [0,0]
          weight_reg_2(1)    = sum(input_reg_2.* weight_reg_2);    %! DPU [0,1]
          weight_reg_3(1)    = sum(input_reg_3.* weight_reg_3);    %! DPU [0,2]
          weight_reg_4(1)    = sum(input_reg_4.* weight_reg_4);    %! DPU [0,3]
          weight_reg_5(1)    = sum(input_reg_5.* weight_reg_5);    %! DPU [0,4]
          weight_reg_6(1)    = sum(input_reg_6.* weight_reg_6);    %! DPU [0,5]
          weight_reg_7(1)    = sum(input_reg_7.* weight_reg_7);    %! DPU [0,6]
          weight_reg_8(1)    = sum(input_reg_8.* weight_reg_8);    %! DPU [0,7]
          weight_reg_9(1)    = sum(input_reg_9.* weight_reg_9);    %! DPU [0,8]
          weight_reg_10(1)   = sum(input_reg_10.* weight_reg_10);  %! DPU [0,9]
          weight_reg_11(1)   = sum(input_reg_11.* weight_reg_11);  %! DPU [0,10]
          weight_reg_12(1)   = sum(input_reg_12.* weight_reg_12);  %! DPU [0,11]
          weight_reg_2(1)    = weight_reg_2(1) + weight_reg_1(1);    %! DPU [1,1]
          weight_reg_3(1)    = weight_reg_3(1) + weight_reg_2(1);    %! DPU [1,2]
          weight_reg_4(1)    = weight_reg_4(1) + weight_reg_3(1);    %! DPU [1,3]
          weight_reg_5(1)    = weight_reg_5(1) + weight_reg_4(1);    %! DPU [1,4]
          weight_reg_6(1)    = weight_reg_6(1) + weight_reg_5(1);    %! DPU [1,5]
          weight_reg_7(1)    = weight_reg_7(1) + weight_reg_6(1);    %! DPU [1,6]
          weight_reg_8(1)    = weight_reg_8(1) + weight_reg_7(1);    %! DPU [1,7]
          weight_reg_9(1)    = weight_reg_9(1) + weight_reg_8(1);    %! DPU [1,8]
          weight_reg_10(1)   = weight_reg_10(1) + weight_reg_9(1);   %! DPU [1,9]
          weight_reg_11(1)   = weight_reg_11(1) + weight_reg_10(1);  %! DPU [1,10]
          weight_reg_12(1)   = weight_reg_12(1) + weight_reg_11(1);  %! DPU [1,11]
          full_mul_reg(resultsweep) = full_mul_reg(resultsweep) + weight_reg_12(1); %! DPU [1,12]

        end
%full_mul_reg= __sl_sigmoid(full_mul_reg); %! DPU [0,12]
%transfer back from RFILE to DiMarch
full_mul_dimarch(sequencesweep*Z-Z+1:sequencesweep*Z)= full_mul_reg;
end
