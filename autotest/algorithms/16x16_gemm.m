%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% BLAS L3 Function -- GEMM
%
% Y = a*A*X + b*Y
%
% A: m x k matrix
% X: k x n matrix
% Y: m x n matrix
% a: scalar coefficient
% b: scalar coefficient
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

m = 16;
k = 16;
n = 16;
rd = 32; % Register Depth
A_mem = [1:m*k];        %! MEM[0,0]
X_mem = ones(1,k*n);    %! MEM[0,0]
Y_mem = [1:m*n];        %! MEM[0,0]
ab_mem = [2:17];        %! MEM[0,0]

A_reg = zeros(1,rd/2);  %! RFILE[0,0]
X_reg = zeros(1,rd/2);  %! RFILE[0,0]
Y_reg = zeros(1,rd/2);  %! RFILE[1,0]
ab_reg = zeros(1,rd/2); %! RFILE[1,0]
r = [0];                %! CDPU[0,0]

ab_reg = ab_mem (1:rd/2);
r = silago_dpu_load_reg_0(ab_reg(1));
a = 0; %! RACCU_VAR
b = 0; %! RACCU_VAR
for i=1:m*n/(rd/2)
    Y_reg = Y_mem( a*rd/2+1: (a+1)*rd/2 );
    Y_reg = Y_reg .* ab_reg(silago_agu_linear_1d(2, 0, rd/2)); %!DPU[0,0]
    for j = 1:k/16
        A_reg = A_mem( ((i-1)*(n/(rd/2))*(k/(rd/2))+(j-1))*rd/2+1 : ((i-1)*(n/(rd/2))*(k/(rd/2))+j)*rd/2 );
        for l = 1 : rd/2
            X_reg = X_mem((l-1)*k+(j-1)*rd/2+1:(l-1)*k+j*rd/2);
            Y_reg(l) = silago_dpu_axpy_acc(A_reg, X_reg, Y_reg(l), r); %! DPU[0,0]
        end
    end
    Y_mem( (i-1)*rd/2+1: i*rd/2 )= Y_reg;
    a = a+1;
end
