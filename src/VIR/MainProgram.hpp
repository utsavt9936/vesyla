#include <exception>
using namespace std;

#ifndef __MainProgram_h__
#define __MainProgram_h__

#include "FunctionDeclaration.hpp"

namespace VIR {
// class FunctionDeclaration;
class MainProgram;
}

namespace VIR {
class MainProgram: public VIR::FunctionDeclaration {
private:
	bool _hasDynamicLoops;

public:
	MainProgram();

public:
	bool hasDynamicLoops() const;

public:
	void hasDynamicLoops(bool hasDynamicLoops_);
};
}

#endif
