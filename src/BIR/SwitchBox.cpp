#include <exception>
using namespace std;

#include "SwitchBox.hpp"
#include "BIRBase.hpp"

BIR::SwitchBox::SwitchBox(int inputNum_, int outputNum_)
{
	_inputNum = inputNum_;
	_outputNum = outputNum_;
	_inputOutputConnections = new int[outputNum_];
}

BIR::SwitchBox::~SwitchBox()
{
	delete [] _inputOutputConnections;
}

void BIR::SwitchBox::setAConnection(int inputIndex_, int outputIndex_, bool enable_)
{
	if (enable_ && inputIndex_ < _inputNum)
	{
	    _inputOutputConnections[outputIndex_] = inputIndex_;
	}
	else
	{
	    _inputOutputConnections[outputIndex_] = -1;
	}
}

int BIR::SwitchBox::getAConnection(int outputIndex_) const
{
	return _inputOutputConnections[outputIndex_];
}

