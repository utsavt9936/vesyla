
% RGB to YUV testcase

% Features:
%  - RGB to YUV with 3 DPUs

rgb =  fi([0.5 0.25 0.3333], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0,0]

ycoe = fi([0.299 0.587 0.114], 1, 16, 15, 'RoundingMethod', 'Floor');          %! RFILE<input> [1,0]
ucoe = fi([-0.14713 -0.28886 +0.436], 1, 16, 15, 'RoundingMethod', 'Floor');   %! RFILE<input> [1,1]
vcoe = fi([0.615 -0.51499 -0.10001], 1, 16, 15, 'RoundingMethod', 'Floor');    %! RFILE<input> [1,2]

y = fi([0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<output> [1,0]
u = fi([0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<output> [1,1]
v = fi([0], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<output> [1,2]

%! RESOURCE_SHARING_BEGIN
y = sum(rgb .* ycoe); %! DPU<sat>[1,0]
u = sum(rgb .* ucoe); %! DPU<sat>[1,1]
v = sum(rgb .* vcoe); %! DPU<sat>[1,2]
%! RESOURCE_SHARING_END
