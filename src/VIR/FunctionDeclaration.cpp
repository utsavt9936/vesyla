#include <exception>
#include <string>
using namespace std;

#include "FunctionDeclaration.hpp"
#include "Declaration.hpp"

vector<VIR::Statement*> & VIR::FunctionDeclaration::body() {
	return _body;
}

string VIR::FunctionDeclaration::name() const {
	return _name;
}

void VIR::FunctionDeclaration::name(const string & name_) {
	_name = name_;
}

vector<VIR::Statement*> & VIR::FunctionDeclaration::totalAssignmentStatements() {
	return _totalAssignmentStatements;
}

