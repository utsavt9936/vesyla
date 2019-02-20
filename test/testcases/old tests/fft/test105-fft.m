N=3; % >> GENERIC
x=[0:10]; % >> x= RFILE [0:0] [0:10] 
w=[11:20]; % >> w= RFILE [0:0] [11:20] 
y=[21:30]; % >> y= RFILE [0:0] [21:30] 
for s=1:N
   ks=2^(N-s+1);  
   kb =2^(s-1)+1;
   ks1=ks-1
   for j=1:2:kb
      kj = 1 + ks*(j-1);
      m=bitRevOrder(0:ks1)
      for k=1:2:ks1
	 k1=kj+m(k);
	 k2=kj+m(k+1);
	 temp=w(j)*x(k2);
         x(k2)=x(k1)-temp; % >>  mDPU [0:0]
         x(k1)=x(k1)+temp; % >>  mDPU [0:0]
      end
   end
end








