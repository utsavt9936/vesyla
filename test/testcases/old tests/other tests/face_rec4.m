%VESYLA code for restoring dientionality in PCA made by Syed Mohammad Asad Hassan Jafri
%this code restores the dimentionality to the original form before the dimentionality reduction.
%To get the dimentionality restoration, we multiply a column of the covarience matrix C with matrix A.
%in total we have K vectors K is caculated by a huristics algorithm that will not be done in this code.
%For this we need k nxn matrices however we have the matrices of sice m*m
%we take a matrix m*1 and myltiply it by A thats n^2 x m to get matrix n^2*1 same as
%the images


% dimensionalityrestoration

%k is a conatant such that k<=M. Its calculated by huristics. for this work we assume that 
%k is already available
k=7;
M = 10; % total images
N = 16; % size of each image
N2 = N * N;
RegFileDepth = 32; % size of a registerfile
HalfRegSize = RegFileDepth/2;

%SRAM to declaration
%actual A matrix columns[n^2 x m]
Image_A_dimarch = [1 :N2]; %! MEM <> [0,0]
Image_A_pong_dimarch = [N2+1 :2*N2]; %! MEM <> [0,0]

%MxM covarience matrix
reduced_matrix_column_dimarch = [1:16]; %! MEM <> [0,1]

%result for multiplication
Multiplication_dimarch=[0 :N*N]; %! MEM <> [0,0]

%Registerfile declaration
Image_A = [1:16]; %! RFILE<> [0,0]
reduced_matrix_column = [17:32]; %! RFILE<> [0,0]
Multiplication = [1:16]; %! RFILE<> [0,1]


for imagesweep= 1:2:N*N

  %sweep across all pisels of an image
  for imagessweep= 1:2:M

    %transfer data from DIMARCH to registerfiles
    Image_A= Image_A_dimarch(imagesweep:imagesweep+Registerfile/2);
    reduced_matrix_column=reduced_matrix_column_dimarch(imagesweep:imagesweep+Registerfile/2);

    % MAC
    multiplication(imagesweep) = sum(Image_A .* reduced_matrix_column_dimarch); %! DPU [0,0]

  end
end




