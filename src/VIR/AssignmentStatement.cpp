#include <exception>
using namespace std;

#include "AssignmentStatement.hpp"
#include "Statement.hpp"
#include "AssignmentType.hpp"

VIR::AssignmentStatement::AssignmentStatement() {
	_twinStatement = 0;
	_isLastResSharingStatement = false;
}

vector<VIR::Name*> & VIR::AssignmentStatement::lhs(){
	return _lhs;
}

void VIR::AssignmentStatement::lhs(vector<Name *> lhs_) {
	_lhs = lhs_;
}

VIR::Expression * VIR::AssignmentStatement::rhs() const {
	return _rhs;
}

void VIR::AssignmentStatement::rhs(Expression * rhs_) {
	_rhs = rhs_;
}

VIR::AssignmentPragma * VIR::AssignmentStatement::pragma() const {
	return _pragma;
}

void VIR::AssignmentStatement::pragma(AssignmentPragma * pragma_) {
	_pragma = pragma_;
}

vector<VIR::SliceName*> & VIR::AssignmentStatement::rhsSliceNames() {
	return _rhsSliceNames;
}

vector<VIR::Identifier*> & VIR::AssignmentStatement::rhsIdentifiers() {
	return _rhsIdentifiers;
}

vector<VIR::Identifier *> & VIR::AssignmentStatement::lhsIdentifiers(){
	return _lhsIdentifiers;
}

vector<VIR::SliceName *> & VIR::AssignmentStatement::lhsSliceNames(){
	return _lhsSliceNames;
}

VIR::VirEnumerations::AssignmentType VIR::AssignmentStatement::type() const {
	return _type;
}

void VIR::AssignmentStatement::type(
		VIR::VirEnumerations::AssignmentType type_) {
	_type = type_;
}

VIR::AssignmentStatement * VIR::AssignmentStatement::twinStatement() const {
	return _twinStatement;
}

void VIR::AssignmentStatement::twinStatement(
		VIR::AssignmentStatement * twinStatement_) {
	_twinStatement = twinStatement_;
}

bool VIR::AssignmentStatement::isLastResSharingStatement() const {
	return _isLastResSharingStatement;
}

void VIR::AssignmentStatement::isLastResSharingStatement(
		bool isLastResSharingStatement_) {
	_isLastResSharingStatement = isLastResSharingStatement_;
}

