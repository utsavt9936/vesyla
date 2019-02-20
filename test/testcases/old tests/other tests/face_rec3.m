%VESYLA code for normalizing in PCA made by Syed Mohammad Asad Hassan Jafri
%this code multiplies a matrix with sice A=M*N^2 with its transpose, where m is the mumber of columns and n^2 is the flattened image
%To get the dimentionalit reduction we multiply (A)^t * A to get a final M*M matrix.

% Covariance

M = 10; % total images
N = 16; % size of each image
N2 = N * N;
RegFileDepth = 32; % size of a registerfile
HalfRegSize = RegFileDepth/2;
QuarterRegSize = RegFileDepth/4;

%total images
M = 10;
%size of each image
N=50;
%size of a registerfile
Registerfile=32;

A_col = M; % size of A columns
A_row = N*N; % size of A rows

%SRAM declaration
%actual Image
Image_A_dimarch = [1 : N2]; %! MEM <> [0,0]
%transpose of the image
Image_At_dimarch = [1 : N2]; %! MEM <> [0,1]
%result for covarience matrix
Covarience_dimarch=[1 : N2]; %! MEM <> [0,1]

%Registerfile declaration
Image_A    = [1:16]; %! RFILE<> [0,0]
Image_At   = [17:32]; %! RFILE<> [0,0]
Covarience = [1:16]; %! RFILE<> [0,1]

for rows = 1 : M

  %sweep across image rows
  for imagessweep = 1 : 2 : M

    %sweep across all pixels of an image
    for pixel_sweep = 0 : HalfRegSize : N2-HalfRegSize

      %transfer data from DIMARCH to registerfiles
      Image_A= Image_A_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize);
      Image_At=Image_At_dimarch(pixel_sweep+1 : pixel_sweep+HalfRegSize);

      %add the result
      Covarience(rows) = sum(Image_A .* Image_At); %! DPU [0,0]

    end

  end

end
