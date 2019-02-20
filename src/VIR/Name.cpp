#include <exception>
using namespace std;

#include "Name.hpp"
#include "Expression.hpp"

VIR::Name::Name() {
	_isDummy = false;
	reverse_bits = NULL;
}

VIR::Name::~Name() {
//	throw "Not yet implemented";
}

bool VIR::Name::isDummy() const {
	return _isDummy;
}

void VIR::Name::isDummy(bool isDummy_) {
	_isDummy = isDummy_;
}

