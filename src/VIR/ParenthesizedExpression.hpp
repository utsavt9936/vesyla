#include <exception>
using namespace std;

#ifndef __ParenthesizedExpression_h__
#define __ParenthesizedExpression_h__

#include "Expression.hpp"

namespace VIR
{
// class Expression;
class ParenthesizedExpression;
} // namespace VIR

namespace VIR
{
class ParenthesizedExpression : public VIR::Expression
{
private:
	VIR::Expression *_value;

public:
	VIR::Expression *value() const;

public:
	void value(Expression *value_);
};
} // namespace VIR

#endif
