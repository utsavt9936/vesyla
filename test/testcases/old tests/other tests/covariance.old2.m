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
%actual Image actually its the image 
Image_A_dimarch = [1 :N*N]; %! MEM <> [0,0]
%Image_A_pong_dimarch = [N*N+1 :2*N*N]; %! MEM <> [0,0]
%transpose of the image
Image_At_dimarch = [1 :N*N]; %! MEM <> [1,0]
%Image_At_pong_dimarch = [N*N+1 :2*N*N]; %! MEM <> [1,0]
%result for covarience matrix
Covarience_dimarch=[1 :N*N]; %! MEM <> [2,0]

%Registerfile declaration
Image_A = [1:32]; %! RFILE<> [0,0]
Image_At = [1:32]; %! RFILE<> [1,0]
Covarience = zeros(1,16); %! RFILE<> [0,1]
mul1 = [0]; %! RFILE<> [1,1]
ia = [1]; %! RFILE<> [1,1]
z = [1]; %! RFILE<> [1,1]
iaddrs = [0]; %! ADDRESS_VAR
%for c = 1: M 
  for d = 1:M*M 
    for k = 1:8 
      Image_A=Image_A_dimarch(k*32-31 : k*32);
      Image_At=Image_At_dimarch(k*32-31 : k*32);
      %sum1(ia) = sum(Image_A .* Image_At); %! DPU [0,0]
      for l=1:32
      mul1 = Image_A(l)*Image_At(l); %! DPU [0,0]
      Covarience(ia)= Covarience(ia)+mul1; %! DPU [0,0]
      end
    end

    if ia==16
        covarience_dimarch(d-15:d) = Covarience(1:16); %its just 1 element
        ia=z*z;%! DPU [0,0]
    end

    ia=ia+1;%! DPU [0,0]
    iaddrs=iaddrs+1;
    Covarience(ia) = z*z;%! DPU [0,0]
  end
%end
      
    


%for rows= 1:M
%sweep across image rows
%for imagessweep= 1:M
 %sweep across all pixels of an image
 %for imagesweep= 1:Registerfile/16-1
  %for regfileblock=1:Registerfile/4-1 
  %transfer data from DIMARCH to registerfiles
  % if(imagesweep<Registerfile/2)
  %imagesweep*((regfileblock*16) -15)
 % imagesweep*((regfileblock*16) -15)+15
  
  %   Image_A= Image_A_dimarch(imagesweep*((regfileblock*16) -15):imagesweep*((regfileblock*16) -15)+15);
  %   Image_At=Image_At_dimarch(imagesweep*((regfileblock*16) -15):imagesweep*((regfileblock*16) -15)+15);
     %add the result
  %   Covarience(regfileblock) = sum(Image_A .* Image_At); %! DPU [0,0]
  % else
  %   Image_A= Image_A_dimarch_pong(imagesweep*regfileblock:imagesweep*regfileblock+Registerfile/2-1);
  %   Image_At=ImaAt_dimarch_pong(imagesweep*regfileblock:imagesweep*regfileblock+Registerfile/2-1);
     %add the result
  %   Covarience(regfileblock) = sum(Image_A .* Image_At); %! DPU [0,0]         
  % end
  %end
  %transfer data Normalized block
  %Covarience_dimarch(imagesweep:imagesweep+15)=Covarience;  
 %end
%end
