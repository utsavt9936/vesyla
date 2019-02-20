
#ifndef _ExpressionEvaluator_H_
#define _ExpressionEvaluator_H_

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "VIR/BinaryOperatorType.hpp"
#include "VIR/UnaryOperatorType.hpp"
#include "VManager/MemoryManager.hpp"
#include <math.h>
#include <map>

class ExpressionEvaluator
{
public:
//! Yu Yang 2017-08-01
// Change to solve compile error caused by passing reference of object in stack
// CHANGE BEGIN
	int evaluateExpressionToInt(VIR::Expression * expression_, int mode_, VIR::ObjectDeclaration * object_, int rangeMode_, std::map<VIR::ObjectDeclaration *, int> & unrolledMapValues);
// CHAGNE END

	bool isExpressionAffine(VIR::Expression * expression_, bool isForLoop_ = false);
	bool isExpressionConstant(VIR::Expression * expression_);
	VIR::Expression * simplifyExpression(VIR::Expression * expression_);

private:
	enum OutputType { otInteger, otFloat, otVir };

	int calculateBinaryOperation(VIR::VirEnumerations::BinaryOperatorType operatorType_, int leftOp_, int rightOp_);
	float calculateBinaryOperation(VIR::VirEnumerations::BinaryOperatorType operatorType_, float leftOp_, float rightOp_);
	int calculateUnaryOperation(VIR::VirEnumerations::UnaryOperatorType operatorType_, int op_);
	bool isBinaryOperatorAffine(VIR::VirEnumerations::BinaryOperatorType operatorType_);
	bool isUnaryOperatorAffine(VIR::VirEnumerations::UnaryOperatorType operatorType_);
	void * simplifyExpressionGeneral(VIR::Expression * expression_, OutputType & outputType_, bool isEvaluationMode_ = false);
};

#endif // _ExpressionEvaluator_H_
