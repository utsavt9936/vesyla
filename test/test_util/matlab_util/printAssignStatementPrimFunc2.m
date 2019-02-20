
function printAssignStatementPrimFunc2(fileID, funcName, op1Str, op1Idx, op1IdxStr, op1Val, op2Str, op2Idx, op2IdxStr, op2Val, outStr, outIdx, outIdxStr, outVal, operatorStr, isFixedPoint)

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
			fprintf(fileID, ' = %s(%s(%d) %s %s(%d)) }', funcName, op1Str, op1Idx, operatorStr, op2Str, op2Idx);
		end
		fprintf(fileID, '\nRD: %s(%2d) = %s;\nRD: %s(%2d) = %s;', op1Str, op1Idx, printValue(op1Val, isFixedPoint), op2Str, op2Idx, printValue(op2Val, isFixedPoint));
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
			fprintf(fileID, ' = %s(%s(%s) %s %s(%s)) }', outStr, outIdxStr, funcName, op1Str, op1IdxStr, operatorStr, op2Str, op2IdxStr);
		end
		fprintf(fileID, '\nRD: %s(%s) = ', op1Str, op1IdxStr);
		fprintf(fileID, '%s; ', printValue(op1Val, isFixedPoint));
		fprintf(fileID, '\nRD: %s(%s) = ', op2Str, op2IdxStr);
		fprintf(fileID, '%s; ', printValue(op2Val, isFixedPoint));
	end
end
