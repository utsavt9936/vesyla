#ifndef __VESYLA_ELABORATE_IDENTIFIER_CONVERSION_ELABORATOR_HPP__
#define __VESYLA_ELABORATE_IDENTIFIER_CONVERSION_ELABORATOR_HPP__

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "VManager/MemoryManager.hpp"
#include "ExpressionEvaluator.hpp"
#include <algorithm>

namespace vesyla
{
namespace elaborate
{
class IdentifierConversionElaborator
{
public:
	struct VarRecord
	{
		string name;
		int size;
	};

private:
	std::unordered_map<string, VarRecord> _var_map;

public:
	void elaborate(VIR::MainProgram *main_);

private:
	VIR::Array *elaborateArray(VIR::Array *array_);
	VIR::AssignmentPragma *elaborateAssignmentPragma(VIR::AssignmentPragma *assignmentPragma_);
	VIR::AssignmentStatement *elaborateAssignmentStatement(VIR::AssignmentStatement *assignmentStatement_);
	VIR::BinaryExpression *elaborateBinaryExpression(VIR::BinaryExpression *binaryExpression_);
	VIR::Complex *elaborateComplex(VIR::Complex *complex_);
	VIR::DebugStatement *elaborateDebugStatement(VIR::DebugStatement *debugStatement_);
	VIR::Expression *elaborateExpression(VIR::Expression *expression_);
	vector<VIR::Expression *> *elaborateExpressionList(vector<VIR::Expression *> *expressionList_);
	VIR::FloatingPoint *elaborateFloatingPoint(VIR::FloatingPoint *floatingPoint_);
	VIR::ForStatement *elaborateForStatement(VIR::ForStatement *forStatement_);
	VIR::FunctionCall *elaborateFunctionCall(VIR::FunctionCall *functionCall_);
	VIR::Expression *elaborateIdentifier(VIR::Identifier *identifier_);
	VIR::IfThenElseStatement *elaborateIfStatement(VIR::IfStatement *ifStatement_);
	VIR::IfThenElseStatement *elaborateIfThenElseStatement(VIR::IfThenElseStatement *ifThenElseStatement_);
	VIR::Integer *elaborateInteger(VIR::Integer *integer_);
	VIR::MainProgram *elaborateMainProgram(VIR::MainProgram *mainProgram_);
	VIR::ParenthesizedExpression *elaborateParenthesizedExpression(VIR::ParenthesizedExpression *parenthesizedExpression_);
	VIR::PragmaStatement *elaboratePragmaStatement(VIR::PragmaStatement *pragmaStatement_);
	VIR::PrimitiveFunctionCall *elaboratePrimitiveFunctionCall(VIR::PrimitiveFunctionCall *primitiveFunctionCall_);
	VIR::RangeExpression *elaborateRangeExpression(VIR::RangeExpression *rangeExpression_);
	VIR::ReferencePragma *elaborateReferencePragma(VIR::ReferencePragma *referencePragma_);
	VIR::SliceName *elaborateSliceName(VIR::SliceName *sliceName_);
	VIR::Statement *elaborateStatement(VIR::Statement *statement_);
	vector<VIR::Statement *> *elaborateStatementList(vector<VIR::Statement *> *statementList_);
	VIR::StringLiteral *elaborateStringLiteral(VIR::StringLiteral *stringLiteral_);
	VIR::UnaryExpression *elaborateUnaryExpression(VIR::UnaryExpression *unaryExpression_);
};
} // namespace elaborate
} // namespace vesyla

#endif // __VESYLA_ELABORATE_IDENTIFIER_CONVERSION_ELABORATOR_HPP__