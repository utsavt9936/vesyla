#include <exception>
using namespace std;

#include "ContileCell.hpp"
#include "InstructionList.hpp"
#include "Sequencer.hpp"
#include "DiMArchCell.hpp"

BIR::ContileCell::ContileCell(int sramDepth_, int sramWidth_) :
	DiMArchCell(sramDepth_, sramWidth_)
{
	_totalInstructionsCount = 0;
	_sequencer = new BIR::Sequencer();
}

BIR::ContileCell::~ContileCell()
{
	delete _sequencer;
}

void BIR::ContileCell::incTotalInstructionsCount(int incValue_)
{
	_totalInstructionsCount += incValue_;
}

BIR::InstructionList & BIR::ContileCell::instructions()
{
	return _instructions;
}

int BIR::ContileCell::totalInstructionsCount() const
{
	return _totalInstructionsCount;
}

BIR::Sequencer * BIR::ContileCell::sequencer() const
{
	return _sequencer;
}

