#include <exception>
#include <string>
using namespace std;

#include "BinaryExpression.hpp"
#include "Expression.hpp"
#include "BinaryOperatorType.hpp"

VIR::Expression * VIR::BinaryExpression::leftOperand() const {
	return _leftOperand;
}

void VIR::BinaryExpression::leftOperand(Expression * leftOperand_) {
	_leftOperand = leftOperand_;
}

VIR::Expression * VIR::BinaryExpression::rightOperand() const {
	return _rightOperand;
}

void VIR::BinaryExpression::rightOperand(Expression * rightOperand_) {
	_rightOperand = rightOperand_;
}

VIR::VirEnumerations::BinaryOperatorType VIR::BinaryExpression::operatorType() const {
	return _operatorType;
}

void VIR::BinaryExpression::operatorType(
		const VIR::VirEnumerations::BinaryOperatorType & operatorType_) {
	_operatorType = operatorType_;
}

string VIR::BinaryExpression::operatorTypeStr() const {
	return VirEnumerations::binaryOperatorTypeStr(_operatorType);
}

string VIR::BinaryExpression::operatorStr() const {
	return VirEnumerations::binaryOperatorStr(_operatorType);
}

