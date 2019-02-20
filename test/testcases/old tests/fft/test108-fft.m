
% FFT - static implementation

N = 8; % Number of FFT points
STAGE_NO = 3; % Stages
r = 0; % initial row
c = 0; % initial column

Dr = [1:N]; %! RFILE<>[r,c]
Di = [1:N]; %! RFILE<>[r+1,c]
Wr = [1:N/2]; %! RFILE<>[r,c+1]
Wi = [1:N/2]; %! RFILE<>[r,c+1]

Tr0 = zeros(1, N/2); %! CDPU<mod=4,out=0>[r,c]
Tr1 = zeros(1, N/2); %! CDPU<mod=4,out=1>[r,c]
Ti0 = zeros(1, N/2); %! CDPU<mod=4,out=0>[r,c+1]
Ti1 = zeros(1, N/2); %! CDPU<mod=4,out=1>[r,c+1]

for stage = 1 : STAGE_NO

	r0        = bitsll(1, stage);
	half_size = bitsra(r0, 1);
	block_no  = bitsra(N, stage);

	for i = 0 : block_no-1
		
		twi = 1;

		for j = 1 : half_size
			k = r0 * i + j;
			kh = k + half_size;

			Tr0(k) = Dr(k) + Dr(kh) .* Wr(twi);
			Tr1(k) = Dr(k) - Dr(kh) .* Wr(twi);

			Ti0(k) = Di(k) + Di(kh) .* Wr(twi);
			Ti1(k) = Di(k) - Di(kh) .* Wr(twi);

			Dr(kh) = Tr1(k) + Di(kh) .* Wi(twi); %! DPU<mod=5,out=0>[r+1,c]
			Dr(k)  = Tr0(k) - Di(kh) .* Wi(twi); %! DPU<mod=5,out=1>[r+1,c]

			Di(k)  = Ti0(k) + Dr(kh) .* Wi(twi); %! DPU<mod=5,out=0>[r+1,c+1]
			Di(kh) = Ti1(k) - Dr(kh) .* Wi(twi); %! DPU<mod=5,out=1>[r+1,c+1]

			twi = twi + block_no;
		end
	end
end

