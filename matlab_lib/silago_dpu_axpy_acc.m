function o = silago_dpu_axpy_acc(x, y, r, a)
	o = (a*sum(x.*y))+r;
	if o>32767
		o = 32767;
	elseif o<-32768
		o = -32768;
	end
