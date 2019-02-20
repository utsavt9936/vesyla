
function printResult(fileID, outStr, outIdx, outVal, isFixedPoint)

	if length(outIdx) == 1
		fprintf(fileID, '\n%s(%2d)=', outStr, outIdx);
		fprintf(fileID,'%s', printValue(outVal, isFixedPoint));
	else
		for i = 1 : length(outIdx)
			fprintf(fileID, '\n%s(%2d)=', outStr, outIdx(i));
			fprintf(fileID,'%s', printValue(outVal(i), isFixedPoint));
		end
	end
end