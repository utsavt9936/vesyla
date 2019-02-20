%VESYLA code for averaging in PCA made by Syed Mohammad Asad Hassan Jafri
%The algorithm assumes that DIMARCH can accomodat three images. Initially 
%the pixel values of image 1 and image 2 (in pong SRAM bank) are added 
%and the result is stored in the DIMARCH block containing image 1.
%At the same time, it is assumed, that the DRAM fills pong sram with
%Image 3 the second loop does the same computation for the pong DIMARCH
%block. Once all the images are added, the final added result is in the
%image 1 DIMARCH block. Then this image1 is multiplied by -1/M to get the
%average    

% Averaging

M = 10; % total images
N = 16; % size of each image
N2 = N * N;
RegFileDepth = 32; % size of a registerfile
HalfRegSize = RegFileDepth/2;

%SRAM declaration
Image1_dimarch     = [1 : N2]; %! MEM <> [0,0]
Image_pong_dimarch = [N2+1 : 2*N2]; %! MEM <> [0,0]
Image_ping_dimarch = [2*N2+1 : 3*N2]; %! MEM <> [0,1]

%Registerfile declaration
Image1_reg = [1:16]; %! RFILE<> [0,0]
Image2_reg = [17:32]; %! RFILE<> [0,0]
result     = [1:16]; %! RFILE<> [0,1]

%sweep across 10 images
for imagessweep= 1:M/2

  %sweep across all pisels of an image
  for pixel_sweep = 0 : HalfRegSize : N2-HalfRegSize

    %transfer data from DIMARCH to registerfiles
    Image1_reg = Image1_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize);
    Image2_reg = Image_pong_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize);

    %add the result
    result = Image1_reg + Image2_reg; %! DPU [0,0]

    %transfer data back to the SRAM block it came from 
    Image1_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize) = result;

  end

end

%Average the images
Image2_reg = Image_pong_dimarch(1:16);

for pixel_sweep = 0 : HalfRegSize : N2-HalfRegSize

  %transfer data from DIMARCH to registerfiles
  Image1_reg = Image1_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize); 

  % multiply the result
  result = Image1_reg .* Image2_reg; %! DPU [0,0]

  %transfer data back to the SRAM block it came from 
  Image1_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize) = result;

end



