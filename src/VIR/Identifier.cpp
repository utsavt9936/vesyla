#include <exception>
#include <string>
using namespace std;

#include "Identifier.hpp"
#include "Name.hpp"
#include "DependencyType.hpp"

VIR::Identifier::Identifier() {
	_object = 0;
	_dependentTo = 0;
	_dependencyType = VIR::VirEnumerations::dtNone;
	_indexDependency = 0;
}

string VIR::Identifier::name() const {
	return _name;
}

void VIR::Identifier::name(const string & name_) {
	_name = name_;
}

VIR::ObjectDeclaration * VIR::Identifier::object() const {
	return _object;
}

void VIR::Identifier::object(VIR::ObjectDeclaration * object_) {
	_object = object_;
}

VIR::AssignmentStatement * VIR::Identifier::dependentTo() const {
	return _dependentTo;
}

void VIR::Identifier::dependentTo(VIR::AssignmentStatement * dependentTo_) {
	_dependentTo = dependentTo_;
}

VIR::VirEnumerations::DependencyType VIR::Identifier::dependencyType() const {
	return _dependencyType;
}

void VIR::Identifier::dependencyType(
		VIR::VirEnumerations::DependencyType dependencyType_) {
	_dependencyType = dependencyType_;
}

VIR::Statement * VIR::Identifier::indexDependency() const {
	return _indexDependency;
}

void VIR::Identifier::indexDependency(VIR::Statement * indexDependency_) {
	_indexDependency = indexDependency_;
}

