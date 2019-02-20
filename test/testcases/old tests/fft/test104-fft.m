
% FFT

N = 64; % Number of FFT points
max_stage = log2(N); % Maximum Stages
row = 1;
column = 1;
address_range = (0:N-1); %! range
phy_address_1 = (0:2:N-2); %! range
phy_address_1 = (0:2:N-1); %! range

load('ArBr.mat','ArBr'); %! RFILE[row,column]; bitrvrs; phy_address_1

load('AiBi.mat','AiBi'); %! RFILE[row,column+1]; bitrvrs; phy_address_2

load('WrWi.mat','WrWi'); %! RFILE[row+1,column]; bitrvrs; address_range

BrBi_copy = zeros(1:N); %! RFILE[row+1,column+1]; address_range

for stage = 1 : max_stage
	k = 1;
	bitrvr1 = bitreverse(phy_address_1, max_stage - stage + 1, 16);
	bitrvr2 = bitreverse(phy_address_2, max_stage - stage + 1, 16);
	limit = 2 ^ (stage-1);
	index = 2 ^ (max_stage - stage);

	for i = 1 : limit
		j = (k : k+index-1);

		A0(j) = ArBr(bitrvr1(j) + 1) + (WrWi(i) .* ArBr(bitrvr2(j) + 1)); %! DPU[row,column]
		A1(j) = ArBr(bitrvr1(j) + 1) - (WrWi(i) .* ArBr(bitrvr2(j) + 1)); %! DPU[row,column]

		B0(j) = AiBi(bitrvr1(j) + 1) + (WrWi(i) .* AiBi(bitrvr2(j) + 1)); %! DPU[row,column+1]
		B1(j) = AiBi(bitrvr1(j) + 1) - (WrWi(i) .* AiBi(bitrvr2(j) + 1)); %! DPU[row,column+1]

		BrBi_copy(j) = A0(j) - (WrWi(i + N/2) .* AiBi(bitrvr2(j) + 1)); %! DPU[row+1,column]
		ArBr(bitrvr1(j)+1) = A1(j) + (WrWi(i + N/2) .* AiBi(bitrvr2(j) + 1)); %! DPU[row+1,column]

		BrBi_copy(j) = B0(j) - (WrWi(i + N/2) .* AiBi(bitrvr2(j) + 1)); %! DPU[row+1,column+1]
		AiBi(bitrvr1(j)+1) = B1(j) - (WrWi(i + N/2) .* AiBi(bitrvr2(j) + 1)); %! DPU[row+1,column+1]

		ArBr(bitrvr2(j) + 1) = BrBi_copy(j); %! RFILE
		AiBi(bitrvr2(j) + 1) = BrBi_copy(j + N/2); %! RFILE

		k = k + index;
	end
end

