
% VESYLA code for normalizing in PCA made
% This code multiplies a matrix with sice A=M*N^2 with its transpose, where m is the mumber of columns and n^2 is the flattened image
% To get the dimensionality reduction we multiply (A)^t * A to get a final M*M matrix.

% Note that M*M should be divisible by the number of words in each Memory block.
% In other words, M*M % MEM_BLOCK_SIZE = 0

M = 8; % Total images
N = 16; % Image Dimension
IMAGE_SIZE = N*N; % Image size
OUTPUT_SIZE = M*M; % The size of the result matrix after covariance calculation
MEM_BLOCK_SIZE = 16; % Number of words in a memory block
RFILE_SIZE = 32; % Size of a RegisterFile

% Memory declarations
imageA_mem     = fi([1 : IMAGE_SIZE], 1, 16, 0); %! MEM<> [0,0] % actual image
imageAt_mem    = fi([1 : IMAGE_SIZE], 1, 16, 0); %! MEM<> [0,1] % image transpose
covariance_mem = fi(zeros(1,OUTPUT_SIZE), 1, 16, 0); %! MEM<> [0,2] % covariance result

% RegFile declarations
imageA     = fi(zeros(1,RFILE_SIZE), 1, 16, 0); %! RFILE<> [0,0]
imageAt    = fi(zeros(1,RFILE_SIZE), 1, 16, 0); %! RFILE<> [0,1]
covariance = fi(zeros(1,MEM_BLOCK_SIZE), 1, 16, 0); %! RFILE<> [0,2]

for i = 1 : OUTPUT_SIZE / MEM_BLOCK_SIZE
  for j = 1 : MEM_BLOCK_SIZE
    for k = 1 : IMAGE_SIZE / RFILE_SIZE

      imageA  = imageA_mem ((k-1)*RFILE_SIZE+1 : k*RFILE_SIZE);
      imageAt = imageAt_mem((k-1)*RFILE_SIZE+1 : k*RFILE_SIZE);
      covariance(j) = covariance(j) + sum(imageA .* imageAt); %! DPU<sat> [0,0]

    end
  end

  covariance_mem((i-1)*MEM_BLOCK_SIZE+1 : i*MEM_BLOCK_SIZE) = covariance;
  covariance(1:MEM_BLOCK_SIZE) = 0; %! DPU [0,0]
end
