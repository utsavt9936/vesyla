#include <exception>
#include <string>
using namespace std;

#ifndef __UnaryExpression_h__
#define __UnaryExpression_h__

#include "Expression.hpp"
#include "UnaryOperatorType.hpp"

namespace VIR {
// class Expression;
class UnaryExpression;
namespace VirEnumerations {
// enum UnaryOperatorType;
}
}

namespace VIR {
class UnaryExpression: public VIR::Expression {
private:
	VIR::Expression * _operand;
private:
	VIR::VirEnumerations::UnaryOperatorType _operatorType;

public:
	VIR::Expression * operand() const;

public:
	void operand(Expression * operand_);

public:
	VIR::VirEnumerations::UnaryOperatorType operatorType() const;

public:
	void operatorType(
			const VIR::VirEnumerations::UnaryOperatorType & operatorType_);

public:
	string operatorTypeStr() const;

public:
	string operatorStr() const;
};
}

#endif
