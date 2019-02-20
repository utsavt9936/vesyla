#include "VIRBase.hpp"

int VIR::VIRBase::id() const {
	return _id;
}

int VIR::VIRBase::lineNumber() const {
	return _lineNumber;
}

void VIR::VIRBase::lineNumber(const int lineNumber_) {
	_lineNumber = lineNumber_;
}

VIR::VirEnumerations::KindType VIR::VIRBase::kind() const {
	return _kind;
}

string VIR::VIRBase::kindStr() const {
	return VirEnumerations::kindStr(_kind);
}

VIR::VIRBase::~VIRBase() {
	//throw "Not yet implemented";
}

