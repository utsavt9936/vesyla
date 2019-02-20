%VESYLA code for normalizing in PCA made by Syed Mohammad Asad Hassan Jafri
%this code multiplies a matrix with sice A=M*N^2 with its transpose, where m is the mumber of columns and n^2 is the flattened image
%To get the dimentionalit reduction we multiply (A)^t * A to get a final M*M matrix.


%total  images
M = 10;
%size of each image
N=16;
%size of a registerfile
Registerfile=32;
%Size of A columns
A_col=M;
%Size of A rows
A_row=N*N;



%SRAM to declaration
%actual Image
Image_A_dimarch = [1 :N*N]; %! MEM <> [0,0]
Image_A_pong_dimarch = [N*N+1 :2*N*N]; %! MEM <> [0,0]
%transpose of the image
Image_At_dimarch = [1 :N*N]; %! MEM <> [0,1]
Image_At_pong_dimarch = [N*N+1 :2*N*N]; %! MEM <> [0,1]
%result for covarience matrix
Covarience_dimarch=[1 :N*N]; %! MEM <> [0,1]

%Registerfile declaration
Image_A = [1:16]; %! RFILE<> [0,0]
Image_At = [17:32]; %! RFILE<> [0,0]
Covarience = [1:16]; %! RFILE<> [0,1]


for rows= 1:M
%sweep across image rows
for imagessweep= 1:2:M
 %sweep across all pisels of an image
 for imagesweep= 1:Registerfile/2-1
  for regfileblock=1:Registerfile/2 
  %transfer data from DIMARCH to registerfiles
  Image_A= Image_A_dimarch(imagesweep*regfileblock:imagesweep*regfileblock+Registerfile/2-1);
  Image_At=Image_At_dimarch(imagesweep*regfileblock:imagesweep*regfileblock+Registerfile/2-1);
  %add the result
  Covarience(regfileblock) = sum(Image_A .* Image_At); %! DPU [0,0]
  end
  %transfer data Normalized block
  Covarience_dimarch(imagesweep:imagesweep+15)=Covarience;  
 end

 for imagesweep= 1:Registerfile/2-1
  for regfileblock=1:Registerfile/2 
  %transfer data from DIMARCH to registerfiles
  Image_A= Image_A_dimarch(imagesweep*regfileblock:imagesweep*regfileblock+Registerfile/2-1);
  Image_At=Image_At_dimarch(imagesweep*regfileblock:imagesweep*regfileblock+Registerfile/2-1);
  %add the result
  Covarience(regfileblock) = sum(Image_A .* Image_At); %! DPU [0,0]
  end
  %transfer data Normalized block
  Covarience_dimarch(imagesweep:imagesweep+15)=Covarience;  
 end
end
end
