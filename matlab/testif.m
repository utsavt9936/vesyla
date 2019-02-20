A = [1, 0]; %! RFILE [0,0]
B = [1, 0]; %! RFILE [0,1]

if A(1) > B(1) %! DPU[0,0:1]
	A(1) = B(1);
	B(2) = A(2);
else
	A(2) = B(2);
	B(1) = A(1);
end
