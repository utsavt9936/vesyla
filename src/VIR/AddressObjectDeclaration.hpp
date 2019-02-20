#include <exception>
using namespace std;

#ifndef __AddressObjectDeclaration_h__
#define __AddressObjectDeclaration_h__

// #include "AssignmentStatement.hpp"
// #include "Expression.hpp"
#include "ObjectDeclaration.hpp"
#include "BinaryOperatorType.hpp"

namespace VIR {
class AssignmentStatement;
class Expression;
// class ObjectDeclaration;
class AddressObjectDeclaration;
namespace VirEnumerations {
// enum BinaryOperatorType;
}
}

namespace VIR {
class AddressObjectDeclaration: public VIR::ObjectDeclaration {
private:
	VIR::AssignmentStatement* _addressIterator;
private:
	VIR::Expression* _iterationAmount;
private:
	VIR::VirEnumerations::BinaryOperatorType _operatorType;

public:
	VIR::AssignmentStatement* addressIterator() const;

public:
	void addressIterator(VIR::AssignmentStatement* addressIterator_);

public:
	VIR::Expression * iterationAmount() const;

public:
	void iterationAmount(VIR::Expression * iterationAmount_);

public:
	void operatorType(
			const VIR::VirEnumerations::BinaryOperatorType & operatorType_);

public:
	VIR::VirEnumerations::BinaryOperatorType operatorType() const;
};
}

#endif
