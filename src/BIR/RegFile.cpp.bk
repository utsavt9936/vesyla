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

#include "RegFile.hpp"

#include "AGU.hpp"
#include "Register.hpp"
#include "BIRBase.hpp"

BIR::RegFile::RegFile(int regDepth_)
{
	_regDepth = regDepth_;
	_hasInitialLoad = false;
	
	_registers = new BIR::Register * [_regDepth];
	for (int index = 0; index < _regDepth; ++index)
		_registers[index] = new BIR::Register();
	
	for (int i = 0; i < 4; ++i)
		_agus[i] = new BIR::AGU();
}

BIR::RegFile::~RegFile()
{
	for (int index = 0; index < _regDepth; ++index)
		delete _registers[index];
	delete []_registers;
	
	for (int i = 0; i < 4; ++i)
		delete _agus[i];
}

BIR::AGU * BIR::RegFile::agu(int index_)
{
	return _agus[index_];
}

int BIR::RegFile::regDepth() const
{
	return _regDepth;
}

bool BIR::RegFile::hasInitialLoad() const
{
	return _hasInitialLoad;
}

void BIR::RegFile::hasInitialLoad(bool hasInitialLoad_)
{
	_hasInitialLoad = hasInitialLoad_;
}

BIR::Register* BIR::RegFile::registers(int index_) const
{
	return _registers[index_];
}

