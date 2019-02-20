%VESYLA code for DBLSTM implementation 

G=32;                       %DRRA(or no of silago blocks) group size
P=16;                       %Weight precision
hiddenSize=320;             %No of columns in the hidden layer matrix    
seqLength =100;           %No of sequences (no of rows in input data)
numLayers=4;                %No of LSTM layers in the DBLSTM network 
input_dim =120;           %No of elements in one sequence (no of columns in the input data)
output_dim=46;              %No of columns in the final output after softmax layer
reg_depth=64;               %size of a registerfile (each is 16 bit)
B= 16;                       %Bits per input element (per channel 16 bits in wav file)  
X= 15;                       %for fractional part
W= 16;                       %elements called in one access
Z= 8;                        %no of elements taken along column from hidden size(320)
%SRAM declaration: store for one group

%weights_ping_dimarch  = [0 : W];   %! MEM <> [0,0]
%input_ping_dimarch    = [0 : W];   %! MEM <> [0,0]
%weights_pong_dimarch  = [0 : W];   %! MEM <> [1,0]
%weights2_pong_dimarch = [0 : W];   %! MEM <> [1,0]
%pm_dimarch            = [0 : W];   %! MEM <> [2,0]
%cell_state_dimarch    = [0 : W];   %! MEM <> [2,0]

%Registerfile declaration
input_reg       = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,0]
weight_reg_f    = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,1]
weight_reg_fs   = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,2]
weight_reg_i    = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,3]
weight_reg_is   = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,4]
weight_reg_g    = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,5]
weight_reg_gs   = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<input> [0,6]
pm_reg_1        = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<output> [1,0]
pm_reg_2        = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<output> [1,1]
pm_reg_3        = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<output> [1,2]
pm_reg_4        = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<output> [1,3]
cell_state_reg  = fi(zeros(1,reg_depth), 1, 16, X, 'RoundingMethod', 'Floor');  %! RFILE<output> [1,4]
%DECLARE MORE PM_REG AND MORE WEIGHT REG
%sweep across 1 sequence

%for sequencesweep= 1:760/W
 %sweep across all elements of a sequence

for sequencesweep= 1:320/Z
  %transfer data from DIMARCH to registerfiles
  %input_reg=input_ping_dimarch(sequencesweep:sequencesweep+16);
  %weight_reg=weights_ping_dimarch(sequencesweep:sequencesweep+16);

for j=1:760/16 %for ft and it 16 at a time
	index=(mod(j-1,8)*8); % to prevent rewrite in pm reg after the inner loop
	%load values from DIMARCH to RFILE 
	for i=1:4
		help=(i-1);
		help= help *2;
		help= help + index;
		pm_reg_1(help+1) = sum(input_reg(1:16) .* weight_reg_f((i-1)*16+1:(i)*16)); %! DPU [0,1]
		pm_reg_1(help+2) = sum(input_reg(1:16) .* weight_reg_fs((i-1)*16+1:(i)*16)); %! DPU [0,2]
		pm_reg_2(help+1) = sum(input_reg(1:16) .* weight_reg_i((i-1)*16+1:(i)*16)); %! DPU [0,3]
		pm_reg_2(help+2) = sum(input_reg(1:16) .* weight_reg_is((i-1)*16+1:(i)*16)); %! DPU [0,4]
	end
end

%for j=1:440/16 %for gt
%index=(mod(j-1,8)*8);
% %load values from DIMARCH to RFILE 
%        for i=1:4
%help=(i-1);
%help= help *2;
%help= help + index;      
%          pm_reg_3((i-1)*2+1)   = sum(input_reg(1:16) .* weight_reg_g((i-1)*16+1:(i)*16));  %! DPU [0,0]
%          pm_reg_3((i-1)*2+2)   = sum(input_reg(1:16) .* weight_reg_gs((i-1)*16+1:(i)*16)); %! DPU [0,0]
%       
%        end
%    end
%end
%  %input_reg=weights_ping_dimarch(sequencesweep+17:sequencesweep+32);(6 of these need to be concurrent with the mac operation if the cycle for sram to reg file and dpu calculation is the same)
%  pm_reg_1=mac_result;  
%  %transfer data back to the SRAM block for partial multiplication results 
%  pm_dimarch(sequencesweep:sequencesweep+16)=mac_result;
%  %load all pm result and add together to get the full multiplication result
%   for k=1:5 %to cover all the 320 results of partial multiplication taken 64 at a time
%       %load the next 64 results of partial multiplication from SRAM to RFILE 1
%      for l=1:(760/2)
%       %load the next values in the register file 2
%       %load the next values in the register file 3
%       %load the next values in the register file 4
%       %load the next values in the register file 5
%        weight_reg_f = weight_reg_f + weight_reg_fs;
%        weight_reg_i = weight_reg_i + weight_reg_is;
%        weight_reg_f = weight_reg_f + pm_reg_1;
%        weight_reg_i = weight_reg_i + pm_reg_2; 
%          end

%      for p=1:(440/2)
%       %load the next values in the register file 6
%       %load the next values in the register file 7
%        weight_reg_g = weight_reg_g + weight_reg_gs;
%        weight_reg_g = weight_reg_g + pm_reg_3;
%          end
%        end
%  full_mul_res=full_mul_res+mac_result;
%  %add the bias matrix
%  full_mul_res=full_mul_res+bias;
%  %apply the sigmoid function to the full result(make a dpu mode for tanh and sigmoid)
%%f_t=sig (weight_reg_f) %! DPU mode sigmoid and tanh
%%i_t=sig (weight_reg_i) %! DPU mode sigmoid and tanh
%%g_t=tah (weight_reg_g) %! DPU mode sigmoid and tanh
%  %elementwise multiply cell_state_reg with full_mul_res
%%load cell state c_t-1 from DiMarch to Rfile for elementwise multplication with ft
%cell_state_reg=cell_state_reg.*f_t;
%%elementwise multiply i_t and g_t and get result in p_t
%%elementwise add c_t and p_t
%for sequencesweep= 1:320/Z
%%transfer data from DIMARCH to registerfiles
%%input_reg=input_ping_dimarch(sequencesweep:sequencesweep+16);
%%weight_reg=weights_ping_dimarch(sequencesweep:sequencesweep+16);
%      for j=1:760/16 %for ot 16 at a time
%      index=(mod(j-1,8)*8); % to prevent rewrite in pm reg after the inner loop
%%load values from DIMARCH to RFILE 
%        for i=1:4
%        help=(i-1);
%        help= help *2;
%        help= help + index;
%            pm_reg_4(help+1)   = sum(input_reg(1:16) .* weight_reg_o((i-1)*16+1:(i)*16));  %! DPU [0,0]
%            pm_reg_4(help+2)   = sum(input_reg(1:16) .* weight_reg_os((i-1)*16+1:(i)*16));  %! DPU [0,0]
%        end
%      end
%end
%%input_reg=weights_ping_dimarch(sequencesweep+17:sequencesweep+32);(6 of these need to be concurrent with the mac operation if the cycle for sram to reg file and dpu calculation is the same)
%pm_reg_1=mac_result;  
%%transfer data back to the SRAM block for partial multiplication results 
%pm_dimarch(sequencesweep:sequencesweep+16)=mac_result;
%%load all pm result and add together to get the full multiplication result
%   for k=1:5 %to cover all the 320 results of partial multiplication taken 64 at a time
%       %load the next 64 results of partial multiplication from SRAM to RFILE 1
%      for l=1:(760/2)
%       %load the next values in the register file 2
%       %load the next values in the register file 3
%       %load the next values in the register file 4
%       %load the next values in the register file 5
%        weight_reg_o = weight_reg_o + weight_reg_os;
%        weight_reg_o = weight_reg_o + pm_reg_4; 
%          end
% end
%elementwise tanh operation on c_t to get q_t
%elementwise multiplication of ot and q_t to get h_t
end

