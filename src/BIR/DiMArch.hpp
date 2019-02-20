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
