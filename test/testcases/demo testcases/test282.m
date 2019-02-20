
% Quantization
% q_32_rfile_4_dpu

q1 = fi([0.5 0.9999 0.9999 0.9999 0.9999 0.9999 0.5 0.9999 0.9999 0.9999 0.5 0.5 0.5 0.5 0.5 0.25 0.3333 0.5 0.5 0.5 0.5 0.2 0.25 0.25 0.3333 0.25 0.1666 0.2 0.1666 0.1666 0.1666 0.2], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0:1, 0]
q2 = fi([0.1666 0.1666 0.1666 0.1428 0.1111 0.125 0.1666 0.1428 0.1111 0.1428 0.1666 0.1666 0.125 0.0909 0.125 0.1111 0.1 0.1 0.1 0.1 0.1 0.1666 0.125 0.0909 0.0833 0.0909 0.1 0.0833 0.1111 0.1 0.1 0.1], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0:1, 2]

x1 = fi([0.012024 0.012024 0.012146 0.012421 0.012665 0.012817 0.011780 0.011383 0.011627 0.012817 0.013733 0.014130 0.014374 0.014893 0.016998 0.012146 0.012024 0.012024 0.012146 0.012421 0.012665 0.012817 0.011780 0.011383 0.011627 0.012817 0.013733 0.014130 0.014374 0.014893 0.016998 0.012146], 1, 16, 15, 'RoundingMethod', 'Floor');  %! RFILE<input> [0:1, 0]
x2 = fi([0.012024 0.012024 0.012146 0.012421 0.012665 0.012817 0.011780 0.011383 0.011627 0.012817 0.013733 0.014130 0.014374 0.014893 0.016998 0.012146 0.012024 0.012024 0.012146 0.012421 0.012665 0.012817 0.011780 0.011383 0.011627 0.012817 0.013733 0.014130 0.014374 0.014893 0.016998 0.012146], 1, 16, 15, 'RoundingMethod', 'Floor');  %! RFILE<input> [0:1, 2]

y1 = fi(zeros(1, 32), 1, 16, 15, 'RoundingMethod', 'Floor');  %! RFILE<output> [0:1, 1]
y2 = fi(zeros(1, 32), 1, 16, 15, 'RoundingMethod', 'Floor');  %! RFILE<output> [0:1, 3]

y1 = x1 .* q1; %! DPU<sat>[0:1, 1]
y2 = x2 .* q2; %! DPU<sat>[0:1, 3]