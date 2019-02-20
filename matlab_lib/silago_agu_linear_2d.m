function addr_v = silago_agu_linear_2d(start_addr, step, num_addr, rep_offset, num_rep)
	for i=1:num_rep
		base_addr = start_addr;
		for j=1:num_addr
			base_addr = base_addr+step;
			if exist('addr_v', 'var')
				addr_v = [addr_v, (i-1)*rep_offset+base_addr];
			else
				addr_v = [(i-1)*rep_offset+base_addr];
			end
		end
	end
end
