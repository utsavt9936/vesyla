#include <exception>
using namespace std;

#include "SliceName.hpp"
#include "Name.hpp"

VIR::SliceName::SliceName() {
	_indexInfo = 0;
}

VIR::Identifier * VIR::SliceName::prefix() const {
	return _prefix;
}

void VIR::SliceName::prefix(Identifier * prefix_) {
	_prefix = prefix_;
}

vector<VIR::Expression*> & VIR::SliceName::suffix() {
	return _suffix;
}

VIR::IndexInfo * VIR::SliceName::indexInfo() const {
	return _indexInfo;
}

void VIR::SliceName::indexInfo(VIR::IndexInfo * indexInfo_) {
	_indexInfo = indexInfo_;
}

