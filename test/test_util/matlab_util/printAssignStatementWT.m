
function printAssignStatementWT(fileID, outStr, outIdx, outIdxStr, outVal, isFixedPoint)

	if length(outIdx) == 1
		fprintf(fileID, '\nWT: %s(%2d) = ', outStr, outIdx);
	else
		fprintf(fileID, '\nWT: %s(%s) = ', outStr, outIdxStr);
	end

	fprintf(fileID,'%s; ', printValue(outVal, isFixedPoint));

	fprintf(fileID, '\n---------------');
end