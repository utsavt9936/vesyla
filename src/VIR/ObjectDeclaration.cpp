#include <exception>
#include <string>
using namespace std;

#include "ObjectDeclaration.hpp"
#include "Declaration.hpp"
#include "ObjectType.hpp"

VIR::ObjectDeclaration::ObjectDeclaration() {
	_pragma = 0;
	_value = 0;
	_objectType = VIR::VirEnumerations::otNone;
	_isFixedPointVariable = false;
}

string VIR::ObjectDeclaration::name() const {
	return _name;
}

void VIR::ObjectDeclaration::name(const string & name_) {
	_name = name_;
}

VIR::NumericLiteral * VIR::ObjectDeclaration::value() const {
	return _value;
}

void VIR::ObjectDeclaration::value(NumericLiteral * value_) {
	_value = value_;
}

VIR::AssignmentPragma * VIR::ObjectDeclaration::pragma() const {
	return _pragma;
}

void VIR::ObjectDeclaration::pragma(VIR::AssignmentPragma * pragma_) {
	_pragma = pragma_;
}

VIR::VirEnumerations::ObjectType VIR::ObjectDeclaration::objectType() const {
	return _objectType;
}

void VIR::ObjectDeclaration::objectType(
		VIR::VirEnumerations::ObjectType objectType_) {
	_objectType = objectType_;
}

bool VIR::ObjectDeclaration::isLoopIndex() const {
	return _objectType == VIR::VirEnumerations::otConstantLoopIndex
			|| _objectType == VIR::VirEnumerations::otNonConstantLoopIndex;
}

bool VIR::ObjectDeclaration::isFixedPointVariable() const {
	return _isFixedPointVariable;
}

void VIR::ObjectDeclaration::isFixedPointVariable(bool isFixedPointVariable_) {
	_isFixedPointVariable = isFixedPointVariable_;
}

