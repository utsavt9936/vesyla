
% 32-point FFT

N = 32; % Number of FFT points
STAGE_NO = 5; % Stages
H_N = N / 2; % half of FFT points number

twid_mem = fi([ 0.999999  0.995185  0.980785  0.956940  0.923880  0.881921  0.831470  0.773010  0.707107  0.634393  0.555570  0.471397  0.382683  0.290285  0.195090  0.098017 ...
				0.000000 -0.098017 -0.195090 -0.290285 -0.382683 -0.471397 -0.555570 -0.634393 -0.707107 -0.773010 -0.831470 -0.881921 -0.923880 -0.956940 -0.980785 -0.995185], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM<> [0,2]
real_mem = fi([-0.458923 -0.691376 -0.289520  0.888947 -0.640106 -0.859985 -0.334503 -0.855652  0.717010  0.975922  0.171753 -0.198395 -0.254669  0.163177  0.906982  0.728821 ...
			   -0.863678  0.893280  0.450684 -0.598694 -0.092041  0.968628  0.332031  0.393005 -0.653809 -0.636963  0.021545 -0.259583  0.794891  0.804474 -0.674164  0.242828], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM<> [0,3]
imag_mem = fi([-0.584747 -0.577057  0.340790 -0.761292 -0.711212  0.929626  0.283905 -0.532837  0.844727 -0.236877 -0.731903 -0.782349  0.261810  0.721436  0.120392 -0.004852 ...
			   -0.524963 -0.289917  0.356476 -0.604523  0.687714  0.684204  0.062103 -0.231964  0.730011  0.345917 -0.165192 -0.682739  0.393707 -0.151520  0.229950  0.583466], 1, 16, 15, 'RoundingMethod', 'Floor'); %! MEM<> [0,4]

Wr = fi(zeros(1, H_N), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][0]
Wi = fi(zeros(1, H_N), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][0]
Dr = fi(zeros(1, N),   1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][1]
Di = fi(zeros(1, N),   1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,4][2]

T = fi(zeros(1, 4), 1, 16, 15, 'RoundingMethod', 'Floor');

for b = 1 : 1

	Wr = twid_mem(1:H_N);
	Wi = twid_mem(H_N+1 : N);
	Dr = real_mem(1:N);
	Di = imag_mem(1:N);

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
