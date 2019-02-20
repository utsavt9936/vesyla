#include <exception>
using namespace std;

#ifndef __ContileCell_h__
#define __ContileCell_h__

#include "InstructionList.hpp"
// #include "Sequencer.hpp"
#include "DiMArchCell.hpp"

namespace BIR
{
class InstructionList;
class Sequencer;
// class DiMArchCell;
class ContileCell;
} // namespace BIR

namespace BIR
{
class ContileCell : public BIR::DiMArchCell
{
private:
	int _totalInstructionsCount;

private:
	BIR::InstructionList _instructions;

private:
	BIR::Sequencer *_sequencer;

public:
	ContileCell(int sramDepth_, int sramWidth_);

public:
	~ContileCell();

public:
	void incTotalInstructionsCount(int incValue_);

public:
	BIR::InstructionList &instructions();

public:
	int totalInstructionsCount() const;

public:
	BIR::Sequencer *sequencer() const;
};
} // namespace BIR

#endif
