#include <exception>
using namespace std;

#ifndef __DRRACluster_h__
#define __DRRACluster_h__

// #include "DiMArch.hpp"
#include "BIRBase.hpp"
#include "VIR/Coordinate.hpp"
#include "DRRACell.hpp"
#include "DiMArch.hpp"

namespace BIR
{
class DiMArch;
// class BIRBase;
class DRRACluster;
} // namespace BIR

namespace BIR
{
class DRRACluster : public BIR::BIRBase
{
private:
	int _rowNum;

private:
	int _colNum;

private:
	BIR::DRRACell ***_drraCells;

private:
	int _optInstructionsCount;

private:
	int _totalUsedRegFiles;

private:
	BIR::DiMArch *_diMArch;

private:
	bool _hasMemoryInstructions;

public:
	DRRACluster(int rowNum_, int colNum_, int regDepth_, int raccuDepth_, int raccuMaxLoopNo_, int dimarchRowNum_, int dimarchColNum_, int sramDepth_, int sramWidth_);
	~DRRACluster();
	BIR::DRRACell *getDRRACell(const VIR::Coordinate &coord_);
	BIR::DRRACell *getDRRACell(int rowIndex_, int colIndex_);
	int rowNum() const;
	int colNum() const;
	int optInstructionsCount() const;
	void optInstructionsCount(int optInstructionsCount_);
	int totalUsedRegFiles() const;
	void incTotalUsedRegFiles();
	BIR::DiMArch *diMArch();
	bool hasMemoryInstructions() const;
	void hasMemoryInstructions(bool hasMemoryInstructions_);
	int instr_count() const;
};
} // namespace BIR

#endif
