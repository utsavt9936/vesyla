// Copyright (C) 2019 Yu Yang
// 
// This file is part of Vesyla.
// 
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

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

