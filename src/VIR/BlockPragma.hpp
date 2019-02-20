#include <exception>
using namespace std;

#ifndef __BlockPragma_h__
#define __BlockPragma_h__

#include "Pragma.hpp"
#include "BlockPragmaType.hpp"

namespace VIR {
// class Pragma;
class BlockPragma;
namespace VirEnumerations {
// enum BlockPragmaType;
}
}

namespace VIR {
class BlockPragma: public VIR::Pragma {
private:
	bool _isBlockBegin;
private:
	VIR::VirEnumerations::BlockPragmaType _blockProgramType;

public:
	bool isBlockBegin() const;

public:
	void isBlockBegin(bool isBlockBegin_);

public:
	VIR::VirEnumerations::BlockPragmaType blockProgramType() const;

public:
	void blockProgramType(
			VIR::VirEnumerations::BlockPragmaType blockProgramType_);
};
}

#endif
