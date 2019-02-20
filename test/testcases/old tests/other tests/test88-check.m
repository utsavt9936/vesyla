
x = [0 :10]; %! RFILE<> [0,1]
t = [22:32]; %! RFILE<> [1,0]
y = [2 :24]; %! RFILE<> [0,0]
z = [0 :21]; %! RFILE<> [1,1]
p = [5 :15]; %! RFILE<> [0,1]
q = [50:61]; %! RFILE<> [1,0]

for m = 1 : 2

  y(m+2) = p(4*m) + q(1); %! DPU [0,0]

  for i = 2 : 2 : 6 

    s = i + 3 

    for j = 1 : 2 : 3 

      r = i + 2*j + 1

      z(2*i) = y(4*m+j) + z(i); %! DPU [0,0]

      for k = 1 : 3

        y(2*k+1) = z(r+k) + x(s+m); %! DPU [1,1]
        x(2*k+1) = y(r+k) + t(s+m); %! DPU [1,0]

      end
    end
  end 
end
