function log_rd(file_handler, op var_obj, var_name, var_index)
	printf(file_handler, '[RD] %s(var_index) => %d', var_name, var_obj(var_index));
