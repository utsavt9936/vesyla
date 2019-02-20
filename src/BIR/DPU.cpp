#include <exception>
using namespace std;

#include "DPU.hpp"
#include "BIRBase.hpp"
#include "DPUMode.hpp"

BIR::DPU::DPU()
{
	_clkCounter = 0;
	_prevDpuInstruction = 0;
}

BIR::BIREnumerations::DPUMode BIR::DPU::mode() const
{
	return _mode;
}

void BIR::DPU::mode(BIR::BIREnumerations::DPUMode mode_)
{
	_mode = mode_;
	
	switch (_mode)
	{
		case BIREnumerations::dmMax:
		case BIREnumerations::dmMin:
			_operandNum = 1;
		break;
	
		case BIREnumerations::dmAdd:
		case BIREnumerations::dmComparison: 
		case BIREnumerations::dmMult:
		case BIREnumerations::dmSub:
		default:
			_operandNum = 2;
		break;
	}
}

int BIR::DPU::clkCounter() const
{
	return _clkCounter;
}

void BIR::DPU::clkCounter(int clkCounter_)
{
	_clkCounter = clkCounter_;
}

BIR::DPUInstruction * BIR::DPU::prevDpuInstruction() const
{
	return _prevDpuInstruction;
}

void BIR::DPU::prevDpuInstruction(BIR::DPUInstruction * prevDpuInstruction_)
{
	_prevDpuInstruction = prevDpuInstruction_;
}

int BIR::DPU::operandNum() const
{
	return _operandNum;
}

