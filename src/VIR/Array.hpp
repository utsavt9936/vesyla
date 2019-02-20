#ifndef __Array_h__
#define __Array_h__

#include "NumericLiteral.hpp"
#include "Expression.hpp"

namespace VIR
{
// class NumericLiteral;
class Array;
} // namespace VIR

namespace VIR
{
class Array : public VIR::NumericLiteral
{
private:
	vector<Expression *> _elements;

public:
	vector<Expression *> &elements();
};
} // namespace VIR

#endif
