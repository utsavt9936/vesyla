#include <exception>
#include <vector>
using namespace std;

#include "InstructionList.hpp"
#include "Instruction.hpp"
#include "BIRBase.hpp"

void BIR::InstructionList::addInstruction(BIR::Instruction * instruction_, bool setInstructionIndex_)
{
	if (setInstructionIndex_)
		instruction_->index = _elements.size();
	_elements.push_back(instruction_);
}

BIR::Instruction * BIR::InstructionList::instruction(int index_) const
{
	return _elements[index_];
}

int BIR::InstructionList::size() const
{
	return _elements.size();
}

void BIR::InstructionList::insert(int index_, BIR::Instruction * instruction_)
{
	_elements.insert(_elements.begin() + index_, instruction_);

	// Set the index of the inserted instruction
	instruction_->index = index_;

	// Update the index of the instructions following the inserted instruction.
	for (unsigned idx = index_+ 1; idx < _elements.size(); ++idx)
		_elements[idx]->index++;
}

BIR::Instruction * BIR::InstructionList::back() const
{
	return _elements.back();
}

void BIR::InstructionList::clear()
{
	return _elements.clear();
}

void BIR::InstructionList::push_back(Instruction* i_)
{
	return _elements.push_back(i_);
}

