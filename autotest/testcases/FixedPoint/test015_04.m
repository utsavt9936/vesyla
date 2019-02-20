
% Fixed-point arithmetic testcase

% Features:
%  - Fixed-point multiply-accumulation
%  - Using DPU of the same cell of the output variable

imageA = fi([0.103601 0.003601 0.003662 0.003723 0.003815 0.003845 0.003540 0.003418 0.003479 0.003845 0.004120 0.004242 0.004303 0.004456 0.005096 0.003662], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0,0]
kernel = fi([0.012024 0.012024 0.012146 0.012421 0.012665 0.012817 0.011780 0.011383 0.011627 0.012817 0.013733 0.014130 0.014374 0.014893 0.016998 0.012146], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0,1]
result = fi(zeros(1,1), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<output> [0,2]

result = sum(fi(imageA .* kernel, 1, 16, 15, 'RoundingMethod', 'Floor')); %! DPU<sat> [0,2]
