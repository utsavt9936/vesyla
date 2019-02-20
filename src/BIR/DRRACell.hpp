#include <exception>
using namespace std;

#ifndef __DRRACell_h__
#define __DRRACell_h__

#include "InstructionList.hpp"
#include "Sequencer.hpp"
#include "BIRBase.hpp"
#include "RegFile.hpp"
#include "DPU.hpp"
#include "SwitchBox.hpp"

namespace BIR
{
class InstructionList;
class Sequencer;
// class BIRBase;
class DRRACell;
} // namespace BIR

namespace BIR
{
class DRRACell : public BIR::BIRBase
{
private:
	BIR::InstructionList _instructions;

private:
	BIR::InstructionList _dpuInstructions;

private:
	BIR::InstructionList _optimizedInstructions;

private:
	BIR::RegFile *_regFile;

private:
	BIR::DPU *_dpu;

private:
	BIR::SwitchBox *_switchD;

private:
	BIR::SwitchBox *_switchR;

private:
	BIR::Sequencer *_sequencer;

private:
	int _optInstructionsCount;

public:
	vector<BIR::Instruction *> instr_list;

public:
	DRRACell(int regDepth_, int raccuDepth_, int raccuMaxLoopNo_);

public:
	~DRRACell();

public:
	BIR::InstructionList &dpuInstructions();

public:
	BIR::InstructionList &instructions();

public:
	BIR::InstructionList &optimizedInstructions();

public:
	BIR::RegFile *regFile() const;

public:
	BIR::DPU *dpu() const;

public:
	void incOptInstructionsCount(int incValue_);

public:
	BIR::SwitchBox *switchD() const;

public:
	BIR::SwitchBox *switchR() const;

public:
	BIR::Sequencer *sequencer() const;

public:
	int optInstructionCount() const;
};
} // namespace BIR

#endif
