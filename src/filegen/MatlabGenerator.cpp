#include "MatlabGenerator.hpp"
namespace vesyla
{
namespace filegen
{
void MatlabGenerator::generate(string directory_)
{
  gen_print_assign_statement(directory_ + "printAssignStatement.m");
  gen_print_assign_prim_func1(directory_ + "printAssignStatementPrimFunc1.m");
  gen_print_assign_prim_func2(directory_ + "printAssignStatementPrimFunc2.m");
  gen_print_assign_prim_func3(directory_ + "printAssignStatementPrimFunc3.m");
  gen_print_assign_wt(directory_ + "printAssignStatementWT.m");
  gen_print_for_statement(directory_ + "printForStatement.m");
  gen_print_result(directory_ + "printResult.m");
  gen_print_storage_transfer(directory_ + "printStorageTransfer.m");
  gen_print_value(directory_ + "printValue.m");
  gen_print_variable(directory_ + "printVariable.m");
}

void MatlabGenerator::gen_print_assign_statement(string filename_)
{
  string str = R"(
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
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_assign_prim_func1(string filename_)
{
  string str = R"(
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
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_assign_prim_func2(string filename_)
{
  string str = R"(
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
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_assign_prim_func3(string filename_)
{
  string str = R"(
function printAssignStatementPrimFunc3(fileID, funcName, op1Str, op1Idx, op1IdxStr, op1Val, op2Str, op2Idx, op2IdxStr, op2Val, op3Str, op3Idx, op3IdxStr, op3Val, outStr, outIdx, outIdxStr, outVal, operatorStr1, operatorStr2, isFixedPoint)

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
			fprintf(fileID, ' = %s(%s(%d) %s (%s(%d) %s %s(%d))) }', outStr, outIdx, funcName, op1Str, op1Idx, operatorStr1, op2Str, op2Idx, operatorStr2, op3Str, op3Idx);
		end
		fprintf(fileID, '\nRD: %s(%2d) = %s;\nRD: %s(%2d) = %s;\nRD: %s(%2d) = %s;', op1Str, op1Idx, printValue(op1Val, isFixedPoint), op2Str, op2Idx, printValue(op2Val, isFixedPoint), op3Str, op3Idx, printValue(op3Val, isFixedPoint));
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
			fprintf(fileID, ' = %s(%s(%s) %s (%s(%s) %s %s(%s))) }', outStr, outIdxStr, funcName, op1Str, op1IdxStr, operatorStr1, op2Str, op2IdxStr, operatorStr2, op3Str, op3IdxStr);
		end
		fprintf(fileID, '\nRD: %s(%s) = ', op1Str, op1IdxStr);
		fprintf(fileID, '%s; ', printValue(op1Val, isFixedPoint));
		fprintf(fileID, '\nRD: %s(%s) = ', op2Str, op2IdxStr);
		fprintf(fileID, '%s; ', printValue(op2Val, isFixedPoint));
		fprintf(fileID, '\nRD: %s(%s) = ', op3Str, op3IdxStr);
		fprintf(fileID, '%s; ', printValue(op3Val, isFixedPoint));
	end
end
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_assign_wt(string filename_)
{
  string str = R"(
function printAssignStatementWT(fileID, outStr, outIdx, outIdxStr, outVal, isFixedPoint)

	if length(outIdx) == 1
		fprintf(fileID, '\nWT: %s(%2d) = ', outStr, outIdx);
	else
		fprintf(fileID, '\nWT: %s(%s) = ', outStr, outIdxStr);
	end

	fprintf(fileID,'%s; ', printValue(outVal, isFixedPoint));

	fprintf(fileID, '\n---------------');
end
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_for_statement(string filename_)
{
  string str = R"(
function printForStatement(fileID, varStr, value)

  fprintf(fileID,'\n\n------------------| For Statement %s=%d |-------------------', varStr, value);

end
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_result(string filename_)
{
  string str = R"(
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
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_storage_transfer(string filename_)
{
  string str = R"(
function printStorageTransfer(fileID, inStr, inIdx, inIdxStr, inVal, outStr, outIdx, outIdxStr, outVal)

	fprintf(fileID, '\n!!! Storage Transfer !!!');

	if length(inIdx) == 1
		fprintf(fileID, '\n{ %s(%d) = %s(%d) }', outStr, outIdx, inStr, inIdx);
	else
		fprintf(fileID, '\n{ %s(%s) = %s(%s) }', outStr, outIdxStr, inStr, inIdxStr);
	end

	fprintf(fileID, '\n---------------');

end
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_value(string filename_)
{
  string str = R"(
function str = printValue(value, isFixedPoint)

	if isFixedPoint == 1
		str = sprintf('%.4f ', value);
	else
		str = sprintf('%2d ', value);
	end

end
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

void MatlabGenerator::gen_print_variable(string filename_)
{
  string str = R"(
function printVariable(fileID, var_, varStr_, isFixedPoint_)

	fprintf(fileID,'\n---------------------------------------------------------');
	fprintf(fileID,'\n     [i]   [%1s]\n', varStr_);
	for index = 1 : length(var_)
		fprintf(fileID,'|->%4d  %s\n', index, printValue(var_(index), isFixedPoint_));
	end
	fprintf(fileID,'*********************************************************');
end
)";
  ofstream ofs(filename_, ofstream::out);
  ofs << str;
}

} // namespace filegen
} // namespace vesyla