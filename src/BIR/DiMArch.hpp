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

#ifndef __DiMArch_h__
#define __DiMArch_h__

#include "DiMArchCell.hpp"
#include "BIRBase.hpp"
#include "VIR/Coordinate.hpp"
#include "ContileCell.hpp"

namespace BIR
{
class DiMArchCell;
// class BIRBase;
class DiMArch;
} // namespace BIR

namespace BIR
{
class DiMArch : public BIR::BIRBase
{
private:
	int _rowNum;

private:
	int _colNum;

private:
	BIR::DiMArchCell ***_dimarchCells;

private:
	int _totalUsedMemWords;

private:
	int _totalInstructionsCount;

public:
	DiMArch(int rowNum_, int colNum_, int sramDepth_, int sramWidth_);

public:
	~DiMArch();

public:
	BIR::ContileCell *getContileCell(int colIndex_);

public:
	BIR::DiMArchCell *getDiMArchCell(const VIR::Coordinate &coord_);

public:
	BIR::DiMArchCell *getDiMArchCell(int rowIndex_, int colIndex_);

public:
	int rowNum() const;

public:
	int colNum() const;

public:
	void incTotalInstructionsCount(int incValue_);

public:
	void incTotalUsedMemWords();

public:
	int totalInstructionsCount() const;

public:
	int totalUsedMemWords() const;

public:
	bool hasInstruction() const;
};
} // namespace BIR

#endif
