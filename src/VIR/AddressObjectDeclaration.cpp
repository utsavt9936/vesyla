#include <exception>
using namespace std;

#include "AddressObjectDeclaration.hpp"
#include "AssignmentStatement.hpp"
#include "Expression.hpp"
#include "ObjectDeclaration.hpp"
#include "BinaryOperatorType.hpp"

VIR::AssignmentStatement* VIR::AddressObjectDeclaration::addressIterator() const {
	return _addressIterator;
}

void VIR::AddressObjectDeclaration::addressIterator(
		VIR::AssignmentStatement* addressIterator_) {
	_addressIterator = addressIterator_;
}

VIR::Expression * VIR::AddressObjectDeclaration::iterationAmount() const {
	return _iterationAmount;
}

void VIR::AddressObjectDeclaration::iterationAmount(
		VIR::Expression * iterationAmount_) {
	_iterationAmount = iterationAmount_;
}

void VIR::AddressObjectDeclaration::operatorType(
		const VIR::VirEnumerations::BinaryOperatorType & operatorType_) {
	_operatorType = operatorType_;
}

VIR::VirEnumerations::BinaryOperatorType VIR::AddressObjectDeclaration::operatorType() const {
	return _operatorType;
}

