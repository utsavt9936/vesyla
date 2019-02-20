
% loop statement testcase (dynamic)

% Features:
%  - Using several loops besides each other

src = [1:16]; %! RFILE<> [0,0] 
dst = [1:16]; %! RFILE<> [0,0]

mulreg = [1:16]; %! RFILE<> [1,0]
mulreg2 = [1:16]; %! RFILE<> [1,1]
addreg = [1:8]; %! RFILE<> [1,0]
addreg2 = [1:8]; %! RFILE<> [1,1]
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
    mulreg2(i) = DCT4x4_MATRIX(6)*src(i+4);%! DPU [0,0]
    mulreg2(i+4) = DCT4x4_MATRIX(2)*src(i);%! DPU [0,1]
end

for i = 1:4
    mulreg2(i+8) = DCT4x4_MATRIX(14)*src(i+12);%! DPU [0,0]
    mulreg2(i+12) = DCT4x4_MATRIX(10)*src(i+8);%! DPU [0,1]
end

for i = 1:4
	addreg(i) = mulreg(i) + mulreg(i+8); %! DPU [0,0]
    addreg(i+4) = mulreg2(i) + mulreg2(i+8); %! DPU [0,1]
end

for i = 1:4
    addreg2(i+4) = mulreg(i+4) + mulreg(i+12); %! DPU [0,0]
    addreg2(i) = mulreg2(i+4) + mulreg2(i+12); %! DPU [0,1]
end

% Combining even and odd terms at each hierarchy levels to 
% calculate the final spatial domain vector

for i = 1:4
    dst(i) = addreg2(i+4) + addreg(i);%! DPU [0,0]
    dst(i+4) = addreg2(i) + addreg(i+4);%! DPU [0,1]
end

for i = 1:4
    dst(i+8) = addreg2(i) + addreg(i+4);%! DPU [0,0]
    dst(i+12) = addreg2(i+4) + addreg(i);%! DPU [0,1]
end