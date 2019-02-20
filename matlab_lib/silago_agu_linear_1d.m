function addr_v = silago_agu_linear_1d(start_addr, step, num_addr)
	if step==0
		addr_v = ones(1, num_addr) .* start_addr;
	else
		addr_v = start_addr:step:((num_addr-1)*step+start_addr);
	endif
end
