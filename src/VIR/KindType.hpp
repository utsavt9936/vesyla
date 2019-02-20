#ifndef __KindType_h__
#define __KindType_h__

#include <string>
using std::string;

namespace VIR
{
namespace VirEnumerations
{
// enum KindType;
}
} // namespace VIR

namespace VIR
{
namespace VirEnumerations
{
// Note: By any change in here also change the implementation of the kindStr function
enum KindType
{
	ktAddressObjectDeclaration,
	ktAddressPragma,
	ktArray,
	ktAssignmentStatement,
	ktBinaryExpression,
	ktBlockPragma,
	ktComplex,
	ktDebugStatement,
	ktDPUChainPragma,
	ktDPUPragma,
	ktFloatingPoint,
	ktForStatement,
	ktFunctionDeclaration,
	ktFunctionCall,
	ktIdentifier,
	ktIfStatement,
	ktIfThenElseStatement,
	ktIndexInfo,
	ktInteger,
	ktLoopObjectDeclaration,
	ktMainProgram,
	ktObjectDeclaration,
	ktParenthesizedExpression,
	ktPragmaConstant,
	ktPragmaExpression,
	ktPragmaStatement,
	ktPrimitiveFunctionCall,
	ktRaccuPragma,
	ktRangeExpression,
	ktSliceName,
	ktStoragePragma,
	ktStringLiteral,
	ktTempVarPragma,
	ktUnaryExpression,
	ktFunctionCallStatement
};

string kindStr(KindType kind_);
} // namespace VirEnumerations
} // namespace VIR

#endif
