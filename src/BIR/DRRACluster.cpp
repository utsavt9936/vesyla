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

#include "DRRACluster.hpp"
#include "DRRACell.hpp"
#include "DiMArch.hpp"
#include "BIRBase.hpp"

BIR::DRRACluster::DRRACluster(int rowNum_, int colNum_, int regDepth_, int raccuDepth_, int raccuMaxLoopNo_, int dimarchRowNum_, int dimarchColNum_, int sramDepth_, int sramWidth_)
{
	_optInstructionsCount = 0;
	_totalUsedRegFiles = 0;
	_hasMemoryInstructions = false;
	_rowNum = rowNum_;
	_colNum = colNum_;
	_diMArch = new BIR::DiMArch(dimarchRowNum_, dimarchColNum_, sramDepth_, sramWidth_);
	_drraCells = new BIR::DRRACell **[_rowNum];

	for (int i = 0; i < _rowNum; ++i)
	{
		_drraCells[i] = new BIR::DRRACell *[_colNum];

		for (int j = 0; j < _colNum; ++j)
			_drraCells[i][j] = new BIR::DRRACell(regDepth_, raccuDepth_, raccuMaxLoopNo_);
	}
}

BIR::DRRACluster::~DRRACluster()
{
	for (int i = 0; i < _rowNum; ++i)
		delete[] _drraCells[i];

	delete[] _drraCells;
	delete _diMArch;
}

BIR::DRRACell *BIR::DRRACluster::getDRRACell(const VIR::Coordinate &coord_)
{
	return _drraCells[coord_.row][coord_.column];
}

BIR::DRRACell *BIR::DRRACluster::getDRRACell(int rowIndex_, int colIndex_)
{
	return _drraCells[rowIndex_][colIndex_];
}

int BIR::DRRACluster::rowNum() const
{
	return _rowNum;
}

int BIR::DRRACluster::colNum() const
{
	return _colNum;
}

int BIR::DRRACluster::optInstructionsCount() const
{
	return _optInstructionsCount;
}

void BIR::DRRACluster::optInstructionsCount(int optInstructionsCount_)
{
	_optInstructionsCount = optInstructionsCount_;
}

int BIR::DRRACluster::totalUsedRegFiles() const
{
	return _totalUsedRegFiles;
}

void BIR::DRRACluster::incTotalUsedRegFiles()
{
	_totalUsedRegFiles++;
}

BIR::DiMArch *BIR::DRRACluster::diMArch()
{
	return _diMArch;
}

bool BIR::DRRACluster::hasMemoryInstructions() const
{
	return _hasMemoryInstructions;
}

void BIR::DRRACluster::hasMemoryInstructions(bool hasMemoryInstructions_)
{
	_hasMemoryInstructions = hasMemoryInstructions_;
}

int BIR::DRRACluster::instr_count() const
{
	int n = 0;
	for (int i = 0; i < _rowNum; i++)
	{
		for (int j = 0; j < _colNum; j++)
		{
			for (auto &instr : _drraCells[i][j]->instr_list)
			{
				if (instr->kind() == BIR::BIREnumerations::bktSRAMInstruction)
				{
					n += 3;
				}
				else
				{
					n += 1;
				}
			}
		}
	}
	return n;
}