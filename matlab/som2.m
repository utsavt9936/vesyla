WEIGHT = 64;
COL = 1;

info_sram = ones(1:16); %! MEM[0,0]
w_sram = ones(1:WEIGHT); %! MEM [0,0]

info_reg = zeros(1:16); %! RFILE [0,0]  % 8 elements for input, 8 elements for [global_best_loc, current_loc, global_best_val, ]
w_reg = zeros(1:16); %! RFILE [0,0]

Cd      = [0 1 0 0 1 0 0 1]; %! RFILE<> [0,0]	% ----[global_loc curr_loc temp dummy update temp3 local_best]
C       = [1 1 1 0 1 0]; %! RFILE<> [0,0]			% ----[curr. prev_best.  seq_t temp2]

i_reg = i_sram;

Cd(1) = 0; %! DPU [0,0]
Cd(2) = 0; %! DPU [0,0]
for i=1:NEURON/COL/2
	Cd(3)=sum(abs(Cd(2)-Cd(1)));
	if Cd(3)>8          %! DPU [0,0]
		Cd(3)=Cd(3)+16;   %! DPU [0,0]
	end
	for j=1:WEIGHT/16
		w_reg = w_sram(i*WEIGHT+j:(i+1)*WEIGHT+j);
		for j=1:16:

		
					for l=1:16        %CHAGEW HERE AND AKE IT 8 WEIGHHTS
								% load from SRAM to RFILE for input sequence
			
			Cd(4) = 2; %! DPU [0,0]
			Dd(4) = 2; %! DPU [0,1]
			for k=1:8 % each weight
				Cd(4)= Cd(4)+2;  %! DPU [0,0]               % *2 increment position 
				Dd(4)= Dd(4)+2;  %! DPU [0,1]               % repeat for other block
				C(3) =__sl_dpu_som_shift(In1(l), Cd(4));   %! DPU [0,0]  % *1 seq unraping from input (It should use bitsll, modified version. to unpack the input to form DD00000000000000)
				D(3) =__sl_dpu_som_shift(In2(l), Dd(4));   %! DPU [0,1]  % repeat for other block
				if Cd(3)< Cd(5)   %! DPU [0,0]              % check for previous best neuron and then update          
					C(4) = W1(k) - C(3);      %! DPU [0,0]       % **equ1**   (data-seq)             
					C(4) = bitsra(C(4),Cd(3)); %! DPU [0,0]      % **equ2**  bitsra(a,2);%! DPU [0,0]   %alpha
%					W1(k) = W1(k) - C(4);     %! DPU [0,0]       % **equ3**  data - last
				end
				if Dd(3)< Dd(5)   %! DPU [0,1]              % repeat for other block                      
					D(4) = W2(k) - D(3);      %! DPU [0,1]
					D(4) = bitsra(D(4),Dd(3)); %! DPU [0,1]
%					W2(k) = W2(k) - D(4);	%! DPU [0,1]
				end

%				W1(k)=W1(k)-C(3); %! DPU <sat> [0,0]    % **equ4** (W-seq)
%				W2(k)=W2(k)-D(3); %! DPU <sat> [0,1]    % repeat for other block
			end 
