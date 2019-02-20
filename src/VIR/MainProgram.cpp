#include <exception>
using namespace std;

#include "MainProgram.hpp"
#include "FunctionDeclaration.hpp"

VIR::MainProgram::MainProgram() {
	_hasDynamicLoops = false;
}

bool VIR::MainProgram::hasDynamicLoops() const {
	return _hasDynamicLoops;
}

void VIR::MainProgram::hasDynamicLoops(bool hasDynamicLoops_) {
	_hasDynamicLoops = hasDynamicLoops_;
}

