
function printAssignStatement(fileID, op1Str, op1Idx, op1IdxStr, op1Val, op2Str, op2Idx, op2IdxStr, op2Val, outStr, outIdx, outIdxStr, outVal, operatorStr, isFixedPoint)

	%fprintf(fileID, '\n\n{ %s(%d) = %s(%d) %s %s(%d) --->', outStr, outIdx, op1Str, op1Idx, operatorStr, op2Str, op2Idx);
	%fprintf(fileID, '\t%s(%d) = %d; %s(%d) = %d; %s(%d) = %d; }', outStr, outIdx, outVal, op1Str, op1Idx, op1Val, op2Str, op2Idx, op2Val);

	if length(op1Idx) == 1
		fprintf(fileID, '\n\n{ %s(%d) = %s(%d) %s %s(%d) }', outStr, outIdx, op1Str, op1Idx, operatorStr, op2Str, op2Idx);
		fprintf(fileID, '\nRD: %s(%2d) = %s;\nRD: %s(%2d) = %s;', op1Str, op1Idx, printValue(op1Val, isFixedPoint), op2Str, op2Idx, printValue(op2Val, isFixedPoint));
	else
		fprintf(fileID, '\n\n{ %s(%s) = %s(%s) %s %s(%s) }', outStr, outIdxStr, op1Str, op1IdxStr, operatorStr, op2Str, op2IdxStr);
		fprintf(fileID, '\nRD: %s(%s) = ', op1Str, op1IdxStr);
		fprintf(fileID, '%s; ', printValue(op1Val, isFixedPoint));
		fprintf(fileID, '\nRD: %s(%s) = ', op2Str, op2IdxStr);
		fprintf(fileID, '%s; ', printValue(op2Val, isFixedPoint));
	end
end