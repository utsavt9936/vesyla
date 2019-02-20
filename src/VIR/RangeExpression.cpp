#include <exception>
using namespace std;

#include "RangeExpression.hpp"
#include "Expression.hpp"

VIR::Expression * VIR::RangeExpression::begin() const {
	return _begin;
}

void VIR::RangeExpression::begin(Expression * begin_) {
	_begin = begin_;
}

VIR::Expression * VIR::RangeExpression::end() const {
	return _end;
}

void VIR::RangeExpression::end(Expression * end_) {
	_end = end_;
}

VIR::Expression * VIR::RangeExpression::increment() const {
	return _increment;
}

void VIR::RangeExpression::increment(Expression * increment_) {
	_increment = increment_;
}

