%VESYLA code for normalizing in PCA made by Syed Mohammad Asad Hassan Jafri
%The algorithm assumes that DIMARCH can accomodate three images. Initially 
%the pixel values of average data are placed in one part of SRAM and image 1 (in pong SRAM bank) are added 
%and the result is stored in the DIMARCH block containing normalized dimarch.
%At the same time, it is assumed, that the DRAM fills ping sram with
%Image 3 the second loop does the same computation for the pong DIMARCH
%block. Once all the images are added, the final added result is in the
%image 1 DIMARCH block. Then this image1 is multiplied by -1/M to get the
%average    

% Addition

M = 10; % total images
N = 16; % size of each image
N2 = N * N;
RegFileDepth = 32; % size of a registerfile
HalfRegSize = RegFileDepth/2;

%SRAM to declaration
average_dimarch    = [1 : N2]; %! MEM <> [0,0]
image_pong_dimarch = [N2+1 : 2*N2]; %! MEM <> [0,0]
normalized_dimarch = [1 : N2]; %! MEM <> [0,1]

%Registerfile declaration
average_reg    = [1:16]; %! RFILE<> [0,0]
image_reg      = [17:32]; %! RFILE<> [0,0]
additionresult = [1:16]; %! RFILE<> [0,1]

%sweep across 10 images
for imagesweep = 1 : M/2

  %sweep across all pixels of an image
  for pixel_sweep = 0 : HalfRegSize : N2-HalfRegSize

    %transfer data from DIMARCH to registerfiles
    average_reg = average_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize);
    image_reg   = image_pong_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize);

    %add the result
    additionresult = average_reg + image_reg; %! DPU [0,0]

    %transfer normalized data block 
    normalized_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize) = additionresult;

  end

end

