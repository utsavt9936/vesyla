r = 0; %initial row
c = 0; %initial column
clipped = [0]; %! RFILE <> [r,c]
zero = [0]; %! RFILE <> [r,c]
one = [1]; %! RFILE <> [r,c]
cn = [-1]; %! RFILE <> [r,c]
cp = [1]; %! RFILE <> [r,c]
din = ones(1,32); %! RFILE <> [r+1,c]
dout = zeros(1,32); %! RFILE <> [r,c+1]

for i=1:32

    if din(i) < cn(1) %! DPU[r, c+1]
        dout(i) = cn(1);
        clipped(1) = one(1);
    else
        dout(i) = din(i);
        clipped(1) = clipped(1);
    end

    if din(i) > cp(1)  %! DPU[r+1, c+1]
        dout(i) = cp(1);
        clipped(1) = one(1);
    else
        dout(i) = din(i);
        clipped(1) = clipped(1);
    end

end
