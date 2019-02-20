#include "KindType.hpp"

#define KIND_STR(kind) case(kind): str = #kind; break;

string VIR::VirEnumerations::kindStr(KindType kind_) {
	string str;

	switch (kind_) {
	KIND_STR(ktAddressObjectDeclaration)
		;
	KIND_STR(ktAddressPragma)
		;
	KIND_STR(ktArray)
		;
	KIND_STR(ktAssignmentStatement)
		;
	KIND_STR(ktBinaryExpression)
		;
	KIND_STR(ktBlockPragma)
		;
	KIND_STR(ktComplex)
		;
	KIND_STR(ktDebugStatement)
		;
	KIND_STR(ktDPUChainPragma)
		;
	KIND_STR(ktDPUPragma)
		;
	KIND_STR(ktFloatingPoint)
		;
	KIND_STR(ktForStatement)
		;
	KIND_STR(ktFunctionDeclaration)
		;
	KIND_STR(ktFunctionCall)
		;
	KIND_STR(ktIdentifier)
		;
	KIND_STR(ktIfStatement)
		;
	KIND_STR(ktIfThenElseStatement)
		;
	KIND_STR(ktIndexInfo)
		;
	KIND_STR(ktInteger)
		;
	KIND_STR(ktLoopObjectDeclaration)
		;
	KIND_STR(ktMainProgram)
		;
	KIND_STR(ktObjectDeclaration)
		;
	KIND_STR(ktParenthesizedExpression)
		;
	KIND_STR(ktPragmaConstant)
		;
	KIND_STR(ktPragmaExpression)
		;
	KIND_STR(ktPragmaStatement)
		;
	KIND_STR(ktPrimitiveFunctionCall)
		;
	KIND_STR(ktRaccuPragma)
		;
	KIND_STR(ktRangeExpression)
		;
	KIND_STR(ktSliceName)
		;
	KIND_STR(ktStoragePragma)
		;
	KIND_STR(ktStringLiteral)
		;
	KIND_STR(ktTempVarPragma)
		;
	KIND_STR(ktUnaryExpression)
		;
	KIND_STR(ktFunctionCallStatement)
		;
	}

	return str.substr(2);
}
