#include <exception>
using namespace std;

#include "Statement.hpp"
#include "VIRBase.hpp"

VIR::Statement::Statement() {
	_controlDependentTo = 0;
	_statementNo = 0;
}

VIR::Statement::~Statement() {
//	throw "Not yet implemented";
}

VIR::Statement * VIR::Statement::controlDependentTo() const {
	return _controlDependentTo;
}

void VIR::Statement::controlDependentTo(VIR::Statement * controlDependentTo_) {
	_controlDependentTo = controlDependentTo_;
}

int VIR::Statement::statementNo() const {
	return _statementNo;
}

void VIR::Statement::statementNo(int statementNo_) {
	_statementNo = statementNo_;
}

