#include <exception>
#include <vector>
using namespace std;

#ifndef __InstructionList_h__
#define __InstructionList_h__

// #include "Instruction.hpp"
#include "BIRBase.hpp"

namespace BIR
{
	class Instruction;
	// class BIRBase;
	class InstructionList;
}

namespace BIR{
class InstructionList: public BIR::BIRBase{
public:
	vector<BIR::Instruction*> _elements;
public:
	void addInstruction(BIR::Instruction * instruction_, bool setInstructionIndex_ = false);
	BIR::Instruction * instruction(int index_) const;
	int size() const;
	void insert(int index_, BIR::Instruction * instruction_);
	BIR::Instruction * back() const;
	void clear();
	void push_back(BIR::Instruction* i_);
};

}

#endif
