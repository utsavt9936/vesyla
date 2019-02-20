
% Covariance testcase

% Features:
%  - Covariance intermediate testing
%  - Using different cells

M = 8; % Total images
N = 16; % Image Dimension
IMAGE_SIZE = N*N; % Image size
OUTPUT_SIZE = M*M; % The size of the result matrix after covariance calculation
MEM_BLOCK_SIZE = 16; % Number of words in a memory block
RFILE_SIZE = 32; % Size of a RegisterFile

% RegFile declarations
imageA    = fi([0.103601 0.003601 0.003662 0.003723 0.003815 0.003845 0.003540 0.003418 0.003479 0.003845 0.004120 0.004242 0.004303 0.004456 0.005096 0.003662 0.002014 0.001404 0.001831 0.002319 0.002106 0.001648 0.001831 0.001770 0.001617 0.001495 0.001404 0.001404 0.001465 0.001495 0.001831 0.001770], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,0] % actual image
imageAt   = fi([0.103601 0.002014 0.001740 0.001343 0.001495 0.002167 0.001801 0.002075 0.002563 0.003326 0.003693 0.003662 0.004120 0.001740 0.001343 0.001404 0.003601 0.001404 0.001740 0.001526 0.001556 0.002228 0.002289 0.002045 0.002594 0.003326 0.003693 0.003662 0.004517 0.001740 0.001465 0.001404], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,1] % image transpose
covariance = fi(zeros(1,MEM_BLOCK_SIZE), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<> [0,2]
dummy      = zeros(1,1); %! RFILE<> [1,0]

for i = 1 : OUTPUT_SIZE / MEM_BLOCK_SIZE
  for j = 1 : MEM_BLOCK_SIZE
    for k = 1 : IMAGE_SIZE / RFILE_SIZE
      covariance(j) = covariance(j) + sum(fi(imageA .* imageAt, 1, 16, 15, 'RoundingMethod', 'Floor')); %! DPU<sat> [0,2]
    end
    
    % Changing DPU mode in order to reset the accumulator value
    dummy(1) = dummy(1) + dummy(1); %! DPU[0,0] 
  end

  covariance(1:MEM_BLOCK_SIZE) = 0; %! DPU [0,0]
end
