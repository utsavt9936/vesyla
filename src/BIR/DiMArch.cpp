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

#include "DiMArch.hpp"
#include "DiMArchCell.hpp"
#include "ContileCell.hpp"
#include "BIRBase.hpp"

BIR::DiMArch::DiMArch(int rowNum_, int colNum_, int sramDepth_, int sramWidth_)
{
	_rowNum = rowNum_;
	_colNum = colNum_;
	_totalUsedMemWords = 0;
	_totalInstructionsCount = 0;
	
	_dimarchCells = new BIR::DiMArchCell ** [_rowNum];
	
	for (int i = 0; i < _rowNum; ++i)
	{
		_dimarchCells[i] = new BIR::DiMArchCell * [_colNum];
	
		if (i == 0)
			for (int j = 0; j < _colNum; ++j)
				_dimarchCells[i][j] = new BIR::ContileCell(sramDepth_, sramWidth_);
		else
			for (int j = 0; j < _colNum; ++j)
				_dimarchCells[i][j] = new BIR::DiMArchCell(sramDepth_, sramWidth_);
	}
}

BIR::DiMArch::~DiMArch()
{
	for (int i = 0; i < _rowNum; ++i)
		delete [] _dimarchCells[i];
	
	delete [] _dimarchCells;
}

BIR::ContileCell * BIR::DiMArch::getContileCell(int colIndex_)
{
	// CONTILE cells are considered as row 0 of the DiMArch
	return (ContileCell *) _dimarchCells[0][colIndex_];
}

BIR::DiMArchCell * BIR::DiMArch::getDiMArchCell(const VIR::Coordinate& coord_)
{
	return _dimarchCells[coord_.row][coord_.column];
}

BIR::DiMArchCell * BIR::DiMArch::getDiMArchCell(int rowIndex_, int colIndex_)
{
	return _dimarchCells[rowIndex_][colIndex_];
}

int BIR::DiMArch::rowNum() const
{
	return _rowNum;
}

int BIR::DiMArch::colNum() const
{
	return _colNum;
}

void BIR::DiMArch::incTotalInstructionsCount(int incValue_)
{
	_totalInstructionsCount += incValue_;
}

void BIR::DiMArch::incTotalUsedMemWords()
{
	++_totalUsedMemWords;
}

int BIR::DiMArch::totalInstructionsCount() const
{
	return _totalInstructionsCount;
}

int BIR::DiMArch::totalUsedMemWords() const
{
	return _totalUsedMemWords;
}

bool BIR::DiMArch::hasInstruction() const
{
	return _totalInstructionsCount > 0;
}

