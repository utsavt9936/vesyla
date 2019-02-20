

#ifndef __BinaryExpression_h__
#define __BinaryExpression_h__

#include "Expression.hpp"
#include "BinaryOperatorType.hpp"
#include <exception>
#include <string>
using namespace std;

namespace VIR
{
// class Expression;
class BinaryExpression;
namespace VirEnumerations
{
// enum BinaryOperatorType;
}
} // namespace VIR

namespace VIR
{
class BinaryExpression : public VIR::Expression
{
private:
	VIR::Expression *_leftOperand;

private:
	VIR::Expression *_rightOperand;

private:
	VIR::VirEnumerations::BinaryOperatorType _operatorType;

public:
	VIR::Expression *leftOperand() const;

public:
	void leftOperand(Expression *leftOperand_);

public:
	VIR::Expression *rightOperand() const;

public:
	void rightOperand(Expression *rightOperand_);

public:
	VIR::VirEnumerations::BinaryOperatorType operatorType() const;

public:
	void operatorType(
			const VIR::VirEnumerations::BinaryOperatorType &operatorType_);

public:
	string operatorTypeStr() const;

public:
	string operatorStr() const;
};
} // namespace VIR

#endif
