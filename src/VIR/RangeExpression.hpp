#include <exception>
using namespace std;

#ifndef __RangeExpression_h__
#define __RangeExpression_h__

#include "Expression.hpp"

namespace VIR {
// class Expression;
class RangeExpression;
}

namespace VIR {
class RangeExpression: public VIR::Expression {
private:
	VIR::Expression * _begin;
private:
	VIR::Expression * _end;
private:
	VIR::Expression * _increment;

public:
	VIR::Expression * begin() const;

public:
	void begin(Expression * begin_);

public:
	VIR::Expression * end() const;

public:
	void end(Expression * end_);

public:
	VIR::Expression * increment() const;

public:
	void increment(Expression * increment_);
};
}

#endif
