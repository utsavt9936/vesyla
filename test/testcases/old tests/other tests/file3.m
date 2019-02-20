
x = [0:10];  %! RFILE<> [0,1]
t = [22:32]; %! RFILE<> [1,0]
y = [11:21]; %! RFILE<> [0,0]
z = [11:21]; %! RFILE<> [1,1]
p = [11:21]; %! RFILE<> [0,1]
q = [11:21]; %! RFILE<> [1,0]

for m = 1 : 2

  y(m+2) = p(4*m) + q(1); %! DPU [0,0]

  for i = 2 : 2 : 6 

    s = 2*i + 3*2 + 1 

    for j = 1 : 2 : 3 

      r = i + 2*j + 1

      z(5*i) = y(4*m+j) + z(i); %! DPU [0,0]

      for k = 1 : 3

        y(2*k+1) = z(r+k) + x(s+m); %! DPU [1,1]
        x(2*k+1) = y(r+k) + t(s+m); %! DPU [1,0]

      end
    end

    for n = 1 : 5
    	x(n) = n + 5;
    end
  end 
end

