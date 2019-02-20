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

