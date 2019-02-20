
function printAssignStatementPrimFunc1(fileID, funcName, op1Str, op1Idx, op1IdxStr, op1Val, outStr, outIdx, outIdxStr, outVal, isFixedPoint)

	if length(op1Idx) == 1
		if(numel(outStr) == 1)
			fprintf(fileID, '\n\n{ %s(%d) = %s(%s(%d)) }', outStr{1}, outIdx{1}, funcName, op1Str, op1Idx);
		else
			fprintf(fileID, '\n\n{ [');
			for i=1:numel(outStr)
				fprintf(fileID, '%s(%d)', outStr{i}, outIdx{i});
				if(i == length(outStr))
					fprintf(fileID, ']');
				else
					fprintf(fileID, ', ');
				end
			end
			fprintf(fileID, ' = %s(%s(%d)) }', funcName, op1Str, op1Idx);
		end
		fprintf(fileID, '\nRD: %s(%2d) = %s;', op1Str, op1Idx, printValue(op1Val, isFixedPoint));
	else
		if(numel(outStr) == 1)
			fprintf(fileID, '\n\n{ %s(%s) = %s(%s(%s)) }', outStr{1}, outIdxStr{1}, funcName, op1Str, op1IdxStr);
		else
			fprintf(fileID, '\n\n{ [');
			for i=1:numel(outStr)
				fprintf(fileID, '%s(%s)', outStr{i}, outIdxStr{i});
				if(i == length(outStr))
					fprintf(fileID, ']');
				else
					fprintf(fileID, ', ');
				end
			end
			fprintf(fileID, ' = %s(%s(%s)) }', funcName, op1Str, op1IdxStr);
		end
		fprintf(fileID, '\nRD: %s(%s) = ', op1Str, op1IdxStr);
		fprintf(fileID, '%s; ', printValue(op1Val, isFixedPoint));
	end
end
