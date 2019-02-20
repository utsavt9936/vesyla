#include <exception>
using namespace std;

#include "ParenthesizedExpression.hpp"
#include "Expression.hpp"

VIR::Expression * VIR::ParenthesizedExpression::value() const {
	return _value;
}

void VIR::ParenthesizedExpression::value(Expression * value_) {
	_value = value_;
}

