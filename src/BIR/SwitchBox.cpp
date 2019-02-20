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

