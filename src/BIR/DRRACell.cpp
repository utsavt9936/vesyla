#include <exception>
using namespace std;

#include "DRRACell.hpp"
#include "DPU.hpp"
#include "InstructionList.hpp"
#include "RegFile.hpp"
#include "Sequencer.hpp"
#include "SwitchBox.hpp"
#include "BIRBase.hpp"

BIR::DRRACell::DRRACell(int regDepth_, int raccuDepth_, int raccuMaxLoopNo_)
{
	_regFile = new BIR::RegFile(regDepth_);
	_dpu = new BIR::DPU();
	_switchD = new BIR::SwitchBox();
	_switchR = new BIR::SwitchBox();
	_sequencer = new BIR::Sequencer(raccuDepth_, raccuMaxLoopNo_);
	_optInstructionsCount = 0;
}

BIR::DRRACell::~DRRACell()
{
	delete _regFile;
	delete _dpu;
	delete _switchD;
	delete _switchR;
	delete _sequencer;
}

BIR::InstructionList & BIR::DRRACell::dpuInstructions()
{
	return _dpuInstructions;
}

BIR::InstructionList & BIR::DRRACell::instructions()
{
	return _instructions;
}

BIR::InstructionList & BIR::DRRACell::optimizedInstructions()
{
	return _optimizedInstructions;
}

BIR::RegFile * BIR::DRRACell::regFile() const
{
	return _regFile;
}

BIR::DPU * BIR::DRRACell::dpu() const
{
	return _dpu;
}

void BIR::DRRACell::incOptInstructionsCount(int incValue_)
{
	_optInstructionsCount += incValue_;
}

BIR::SwitchBox * BIR::DRRACell::switchD() const
{
	return _switchD;
}

BIR::SwitchBox * BIR::DRRACell::switchR() const
{
	return _switchR;
}

BIR::Sequencer * BIR::DRRACell::sequencer() const
{
	return _sequencer;
}

int BIR::DRRACell::optInstructionCount() const
{
	return _optInstructionsCount;
}

