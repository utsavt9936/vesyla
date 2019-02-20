
function printVariable(fileID, var_, varStr_, isFixedPoint_)

	fprintf(fileID,'\n---------------------------------------------------------');
	fprintf(fileID,'\n     [i]   [%1s]\n', varStr_);
	for index = 1 : length(var_)
		fprintf(fileID,'|->%4d  %s\n', index, printValue(var_(index), isFixedPoint_));
	end
	fprintf(fileID,'*********************************************************');
end
