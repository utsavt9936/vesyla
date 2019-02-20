#include <exception>
#include <string>
using namespace std;

#include "Instruction.hpp"
#include "BIRBase.hpp"

BIR::Instruction::Instruction()
{
	minScheduledClkCycle = 0;
	maxScheduledClkCycle = 0;
	isVector = false;
	twinStatementNo = -1;
	isInResSharingRegion = false;
}

BIR::Instruction::~Instruction()
{
	//	throw "Not yet implemented";
}