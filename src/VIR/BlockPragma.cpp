#include <exception>
using namespace std;

#include "BlockPragma.hpp"
#include "Pragma.hpp"
#include "BlockPragmaType.hpp"

bool VIR::BlockPragma::isBlockBegin() const
{
	return _isBlockBegin;
}

void VIR::BlockPragma::isBlockBegin(bool isBlockBegin_)
{
	_isBlockBegin = isBlockBegin_;
}

VIR::VirEnumerations::BlockPragmaType VIR::BlockPragma::blockProgramType() const
{
	return _blockProgramType;
}

void VIR::BlockPragma::blockProgramType(
		VIR::VirEnumerations::BlockPragmaType blockProgramType_)
{
	_blockProgramType = blockProgramType_;
}
