#include <exception>
using namespace std;

#include "LoopObjectDeclaration.hpp"
#include "ForStatement.hpp"
#include "ObjectDeclaration.hpp"

VIR::ForStatement * VIR::LoopObjectDeclaration::forStatement() const {
	return _forStatement;
}

void VIR::LoopObjectDeclaration::forStatement(
		VIR::ForStatement * forStatement_) {
	_forStatement = forStatement_;
}

