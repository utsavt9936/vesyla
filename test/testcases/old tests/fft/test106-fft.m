
N = 4;

x = [0 :10]; %! RFILE<> [0,0]
w = [11:20]; % >> RFILE<> [0,1]
y = [21:30]; % >> RFILE<> [1,0]

ks2 = 2^(N-1) - 1;

for s = 1 : N 

    ks  = 2^(N-s+1);
    ks1 = ks - 1;
    kb  = 2^(s-1);

    for j = 1 : kb

        kj = 1 + ks * (j-1);
        br = bitrev(0:ks1);
        wbr = bitrev(0:ks2);
        kw = wbr(j) + 1;

        for k = 1 : 2 : ks-1

            k1 = kj + br(k);
            k2 = kj + br(k+1);
            temp = w(kw) * x(k2)
            x(k2) = x(k1) - temp; %! DPU [0,0]
            x(k1) = x(k1) + temp; %! DPU [0,0]

        end;
    end;
end; 
