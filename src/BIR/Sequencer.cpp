#include <exception>
#include <map>
using namespace std;

#include "Sequencer.hpp"
#include "InstructionList.hpp"
#include "RACCU.hpp"
#include "BIRBase.hpp"

BIR::Sequencer::Sequencer(int raccuDepth_, int raccuMaxLoopNo_)
{
	sequencerMaxClk = 0;
	
	_raccu = raccuDepth_ != 0 ? new BIR::RACCU(raccuDepth_, raccuMaxLoopNo_) : 0;
}

BIR::Sequencer::Sequencer()
{
	sequencerMaxClk = 0;
	_raccu = 0;
}

BIR::Sequencer::~Sequencer()
{
	if (_raccu)
		delete _raccu;
}

BIR::RACCU * BIR::Sequencer::raccu() const
{
	return _raccu;
}

