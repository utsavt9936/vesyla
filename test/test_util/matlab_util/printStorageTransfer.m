
function printStorageTransfer(fileID, inStr, inIdx, inIdxStr, inVal, outStr, outIdx, outIdxStr, outVal)

	fprintf(fileID, '\n!!! Storage Transfer !!!');

	if length(inIdx) == 1
		fprintf(fileID, '\n{ %s(%d) = %s(%d) }', outStr, outIdx, inStr, inIdx);
	else
		fprintf(fileID, '\n{ %s(%s) = %s(%s) }', outStr, outIdxStr, inStr, inIdxStr);
	end

	fprintf(fileID, '\n---------------');

end