
% loop statement testcase (static)

% Features:
%  - Using three loops besides each other
%  - Using a different statement

src = [1:16]; %! RFILE<> [0,0] 
mulreg = [1:16]; %! RFILE<> [1,0]
addreg = [1:8]; %! RFILE<> [1,2]
DCT4x4_MATRIX = [1:16]; %! RFILE<> [0,2]

for i=1:4
    mulreg(i) = DCT4x4_MATRIX(5)*src(i+4);%! DPU [0,0]
    mulreg(i+4) = DCT4x4_MATRIX(1)*src(i);%! DPU [0,1]
end

for i = 1:4
    mulreg(i+8) = DCT4x4_MATRIX(13)*src(i+12);%! DPU [0,0]
    mulreg(i+12) = DCT4x4_MATRIX(9)*src(i+8);%! DPU [0,1]
end

for i = 1:4
	addreg(i) = mulreg(i) + mulreg(i+8); %! DPU [0,0]
end
