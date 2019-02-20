#include <exception>
#include <string>
using namespace std;

#include "UnaryExpression.hpp"
#include "Expression.hpp"
#include "UnaryOperatorType.hpp"

VIR::Expression * VIR::UnaryExpression::operand() const {
	return _operand;
}

void VIR::UnaryExpression::operand(Expression * operand_) {
	_operand = operand_;
}

VIR::VirEnumerations::UnaryOperatorType VIR::UnaryExpression::operatorType() const {
	return _operatorType;
}

void VIR::UnaryExpression::operatorType(
		const VIR::VirEnumerations::UnaryOperatorType & operatorType_) {
	_operatorType = operatorType_;
}

string VIR::UnaryExpression::operatorTypeStr() const {
	return VirEnumerations::unaryOperatorTypeStr(_operatorType);
}

string VIR::UnaryExpression::operatorStr() const {
	return VirEnumerations::unaryOperatorStr(_operatorType);
}

