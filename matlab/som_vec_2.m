NUM_SOM = 1;
NUM_NEURON = 2;
NUM_WEIGHT = 32;
NUM_COL = 2;
NUM_NEURON_PER_COL = NUM_NEURON / NUM_COL;
BETA_FLOOR_VALUE = 1;
BETA_DECAY_FACTOR = 0;
HALF_NUM_NEURON = NUM_NEURON/2+1;
HALF_NUM_NEURON_HIGH = 1;
HALF_NUM_NEURON_LOW = 1;

i_sram_0 = fi([0.105601 0.004014 0.001740 0.00343 0.001495 0.005167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.304120 0.51740 0.001343 0.51404 0.003601 0.001404 0.008740 0.08526 0.00186 0.002228 0.002289 0.002045 0.00594 0.003326 0.003693 0.08662 0.304517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM [0,0]
w_sram_0 = fi([0.103601 0.002014 0.001740 0.001343 0.001495 0.002167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.004120 0.001740 0.001343 0.001404 0.003601 0.001404 0.001740 0.001526 0.001556 0.002228 0.002289 0.002045 0.002594 0.003326 0.003693 0.003662 0.004517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM [0,0]
%i_reg_0 = fi([0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,0]
%w_reg_0 = fi([0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,0]
i_reg_0 = fi([0.105601 0.004014 0.001740 0.00343 0.001495 0.005167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.304120 0.51740 0.001343 0.51404 0.003601 0.001404 0.008740 0.08526 0.00186 0.002228 0.002289 0.002045 0.00594 0.003326 0.003693 0.08662 0.304517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,0]
w_reg_0 = fi([0.103601 0.002014 0.001740 0.001343 0.001495 0.002167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.004120 0.001740 0.001343 0.001404 0.003601 0.001404 0.001740 0.001526 0.001556 0.002228 0.002289 0.002045 0.002594 0.003326 0.003693 0.003662 0.004517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,0]
i_sram_1 = fi([0.105601 0.004014 0.001740 0.00343 0.001495 0.005167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.304120 0.51740 0.001343 0.51404 0.003601 0.001404 0.008740 0.08526 0.00186 0.002228 0.002289 0.002045 0.00594 0.003326 0.003693 0.08662 0.304517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM [0,1]
w_sram_1 = fi([0.103601 0.002014 0.001740 0.001343 0.001495 0.002167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.004120 0.001740 0.001343 0.001404 0.003601 0.001404 0.001740 0.001526 0.001556 0.002228 0.002289 0.002045 0.002594 0.003326 0.003693 0.003662 0.004517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM [0,1]
%i_reg_0 = fi([0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,0]
%w_reg_0 = fi([0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,0]
i_reg_1 = fi([0.105601 0.004014 0.001740 0.00343 0.001495 0.005167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.304120 0.51740 0.001343 0.51404 0.003601 0.001404 0.008740 0.08526 0.00186 0.002228 0.002289 0.002045 0.00594 0.003326 0.003693 0.08662 0.304517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,1]
w_reg_1 = fi([0.103601 0.002014 0.001740 0.001343 0.001495 0.002167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.004120 0.001740 0.001343 0.001404 0.003601 0.001404 0.001740 0.001526 0.001556 0.002228 0.002289 0.002045 0.002594 0.003326 0.003693 0.003662 0.004517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [0,1]

% info_reg:
%   [1] current location
%   [2] current value
%   [3] best location
%   [4] best value
%   [5] current local best location
%   [6] current local best value
%   [7] Distance between current neuron and best neuron
%   [8] Scale factor beta
%   [9] Factor to decay beta in each input sequence training
%   [10] TEMP VAR to hold half of the neuron size;
%   [11] TEMP VAR to hold shift constant = 8;

INDEX_CURR_LOC = 1;
INDEX_CURR_VAL = 2;
INDEX_BEST_LOC = 3;
INDEX_BEST_VAL = 4;
INDEX_CURR_LOCAL_BEST_LOC = 5;
INDEX_CURR_LOCAL_BEST_VAL = 6;
INDEX_DISTANCE = 7;
INDEX_BETA = 8;
INDEX_BETA_DECAY_FACTOR = 9;
INDEX_HALF_NUM_NEURON = 10;
INDEX_SHIFT_CONST = 11;
INDEX_BETA2 = 12;

info_reg_0 = [0 0 0 0 0 0 0 0 0 1 8 0 0 0 0 0]; %! RFILE [1,0]
info_f_reg_0 = fi([0 0 0 0.999 0 0.999 0 0.999 0.99 0 0 0.999 0 0 0 0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [1,0]
info_reg_1 = [0 0 0 0 0 0 0 0 0 1 8 0 0 0 0 0]; %! RFILE [1,1]
info_f_reg_1 = fi([0 0 0 0.999 0 0.999 0 0.999 0.99 0 0 0.999 0 0 0 0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE [1,1]

for i=1:NUM_NEURON_PER_COL
	info_f_reg_0(INDEX_CURR_VAL) = sum(abs(w_reg_0 - i_reg_0)); %! DPU[0,0]
	info_f_reg_1(INDEX_CURR_VAL) = sum(abs(w_reg_1 - i_reg_1)); %! DPU[0,1]
	if info_f_reg_0(INDEX_CURR_VAL) < info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL) %! DPU [1,0]
		info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL) = info_f_reg_0(INDEX_CURR_VAL);
	else
		info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL) = info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL);
	end
	if info_f_reg_1(INDEX_CURR_VAL) < info_f_reg_1(INDEX_CURR_LOCAL_BEST_VAL) %! DPU [1,1]
		info_f_reg_1(INDEX_CURR_LOCAL_BEST_VAL) = info_f_reg_1(INDEX_CURR_VAL);
	else
		info_f_reg_1(INDEX_CURR_LOCAL_BEST_VAL) = info_f_reg_1(INDEX_CURR_LOCAL_BEST_VAL);
	end
	info_reg_0(INDEX_CURR_LOC) = info_reg_0(INDEX_CURR_LOC) + 2; %! DPU [1,0]
	info_reg_1(INDEX_CURR_LOC) = info_reg_1(INDEX_CURR_LOC) + 2; %! DPU [1,1]
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL) < info_reg_1(INDEX_CURR_LOCAL_BEST_VAL) %! DPU[1, 0:1]
	info_f_reg_1(INDEX_CURR_LOCAL_BEST_LOC) = info_f_reg_0(INDEX_CURR_LOCAL_BEST_LOC);
	info_f_reg_1(INDEX_CURR_LOCAL_BEST_VAL) = info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL);
else
	info_f_reg_0(INDEX_CURR_LOCAL_BEST_LOC) = info_f_reg_1(INDEX_CURR_LOCAL_BEST_LOC);
	info_f_reg_0(INDEX_CURR_LOCAL_BEST_VAL) = info_f_reg_1(INDEX_CURR_LOCAL_BEST_VAL);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

info_reg_0(INDEX_BEST_LOC) = info_reg_0(INDEX_CURR_LOCAL_BEST_LOC);
info_reg_1(INDEX_BEST_LOC) = info_reg_1(INDEX_CURR_LOCAL_BEST_LOC);

info_reg_0(INDEX_CURR_LOC) = 0; %! DPU[1,0]
info_reg_1(INDEX_CURR_LOC) = 0; %! DPU[1,1]
for j=1:NUM_NEURON_PER_COL
	info_reg_0(INDEX_DISTANCE) = sum(abs(info_reg_0(INDEX_CURR_LOC) - info_reg_0(INDEX_BEST_LOC))); %! DPU [1,0]
	info_reg_1(INDEX_DISTANCE) = sum(abs(info_reg_1(INDEX_CURR_LOC) - info_reg_1(INDEX_BEST_LOC))); %! DPU [1,1]
	if info_reg_0(INDEX_DISTANCE) > 15 %! DPU[1,0]
		info_reg_0(INDEX_DISTANCE) = 15; %! DPU[1,0]
	else
		info_reg_0(INDEX_DISTANCE) = info_reg_0(INDEX_DISTANCE);
	end
	if info_reg_1(INDEX_DISTANCE) > 15 %! DPU[1,1]
		info_reg_1(INDEX_DISTANCE) = 15; %! DPU[1,1]
	else
		info_reg_1(INDEX_DISTANCE) = info_reg_1(INDEX_DISTANCE);
	end
	if info_reg_0(INDEX_DISTANCE) >= info_reg_0(INDEX_HALF_NUM_NEURON) %! DPU [1,0]
		info_reg_0(INDEX_DISTANCE) = info_reg_0(INDEX_DISTANCE) - info_reg_0(INDEX_HALF_NUM_NEURON); %! DPU [1,0]
	else
		info_reg_0(INDEX_DISTANCE) = info_reg_0(INDEX_DISTANCE) - 0; %! DPU [1,0]
	end
	if info_reg_1(INDEX_DISTANCE) >= info_reg_1(INDEX_HALF_NUM_NEURON) %! DPU [1,1]
		info_reg_1(INDEX_DISTANCE) = info_reg_1(INDEX_DISTANCE) - info_reg_1(INDEX_HALF_NUM_NEURON); %! DPU [1,1]
	else
		info_reg_1(INDEX_DISTANCE) = info_reg_1(INDEX_DISTANCE) - 0; %! DPU [1,1]
	end
	info_f_reg_0(INDEX_BETA2) = bitsra(info_f_reg_0(INDEX_BETA), info_reg_0(INDEX_DISTANCE)); %! DPU [1,0]
	info_f_reg_1(INDEX_BETA2) = bitsra(info_f_reg_1(INDEX_BETA), info_reg_1(INDEX_DISTANCE)); %! DPU [1,1]
	w_reg_0 = i_reg_0 - w_reg_0; %! DPU [0,0]
	w_reg_1 = i_reg_1 - w_reg_1; %! DPU [0,1]
%	w_reg_0(1:NUM_WEIGHT) = w_reg_0(1:NUM_WEIGHT) .* info_f_reg_0(INDEX_BETA2); %!DPU[0,0]
%	w_reg_1(1:NUM_WEIGHT) = w_reg_1(1:NUM_WEIGHT) .* info_f_reg_1(INDEX_BETA2); %!DPU[0,1]
	for k=1:NUM_WEIGHT
		w_reg_0(k) = w_reg_0(k) .* info_f_reg_0(INDEX_BETA2); %!DPU[0,0]
		w_reg_1(k) = w_reg_1(k) .* info_f_reg_1(INDEX_BETA2); %!DPU[0,1]
	end
end

info_f_reg_0(INDEX_BETA) = info_f_reg_0(INDEX_BETA) * info_f_reg_0(INDEX_BETA_DECAY_FACTOR); %!DPU[1,0]
info_f_reg_1(INDEX_BETA) = info_f_reg_1(INDEX_BETA) * info_f_reg_1(INDEX_BETA_DECAY_FACTOR); %!DPU[1,1]
if info_f_reg_0(INDEX_BETA) > 0.01 %! DPU [1,0]
	info_f_reg_0(INDEX_BETA) = info_f_reg_0(INDEX_BETA) + 0; %! DPU [1,0]
else
	info_f_reg_0(INDEX_BETA) = 0; %! DPU[1,0]
end
if info_f_reg_1(INDEX_BETA) > 0.01 %! DPU [1,1]
	info_f_reg_1(INDEX_BETA) = info_f_reg_1(INDEX_BETA) + 0; %! DPU [1,1]
else
	info_f_reg_1(INDEX_BETA) = 0; %! DPU[1,1]
end

