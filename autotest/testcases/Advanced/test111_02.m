
% 16-point FFT

N = 16; % Number of FFT points
STAGE_NO = 4; % Stages
H_N = N / 2; % half of FFT points number
M_BLOCK_SIZE = 16;

twid_mem = fi([ 0.999999  0.995185  0.980785  0.956940  0.923880  0.881921  0.831470  0.773010  0.000000 -0.098017 -0.195090 -0.290285 -0.382683 -0.471397 -0.555570 -0.634393], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM<> [0,2]
real_mem = fi([-0.458923 -0.691376 -0.289520  0.888947 -0.640106 -0.859985 -0.334503 -0.855652  0.717010  0.975922  0.171753 -0.198395 -0.254669  0.163177  0.906982  0.728821], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM<> [0,3]
imag_mem = fi([-0.584747 -0.577057  0.340790 -0.761292 -0.711212  0.929626  0.283905 -0.532837  0.844727 -0.236877 -0.731903 -0.782349  0.261810  0.721436  0.120392 -0.004852], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM<> [0,4]

m_reg = fi(zeros(1, M_BLOCK_SIZE), 1, 16, 15, 'RoundingMethod', 'Floor');
Wr = fi(zeros(1, H_N), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][0]
Wi = fi(zeros(1, H_N), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][0]
Dr = fi(zeros(1, N),   1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][1]
Di = fi(zeros(1, N),   1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][2]
T  = fi(zeros(1, 4),   1, 16, 15, 'RoundingMethod', 'Floor');

for b = 1 : 1

	m_reg = twid_mem(1:M_BLOCK_SIZE);
	Wr = m_reg(1 : H_N);
	Wi = m_reg(H_N+1 : N);

	Dr = real_mem(1:M_BLOCK_SIZE);
	Di = imag_mem(1:M_BLOCK_SIZE);

	[Dr, i] = bitrevorder(Dr);
	[Di, i] = bitrevorder(Di);

	for stage = 1 : STAGE_NO

		r0        = bitsll(1, stage);
		half_size = bitsra(r0, 1);
		block_no  = bitsra(N, stage);

		for i = 0 : block_no-1
			
			twi = 1;

			for j = 1 : half_size

				k1 = r0 * i + j;
				k2 = k1 + half_size;

				%! RESOURCE_SHARING_BEGIN
				T(1) = fi(Dr(k2) .* Wr(twi), 1, 16, 15, 'RoundingMethod', 'Floor');
				T(2) = fi(Di(k2) .* Wi(twi), 1, 16, 15, 'RoundingMethod', 'Floor');
				T(3) = fi(Di(k2) .* Wr(twi), 1, 16, 15, 'RoundingMethod', 'Floor');
				T(4) = fi(Dr(k2) .* Wi(twi), 1, 16, 15, 'RoundingMethod', 'Floor');

				Dr(k2) = Dr(k1) - T(1) + T(2); %! DPU [0,4]
				Dr(k1) = Dr(k1) + T(1) - T(2); %! DPU [0,4]
				Di(k2) = Di(k1) - T(3) - T(4); %! DPU [0,4]
				Di(k1) = Di(k1) + T(3) + T(4); %! DPU [0,4]
				%! RESOURCE_SHARING_END

				twi = twi + block_no;
			end
		end
	end
end
