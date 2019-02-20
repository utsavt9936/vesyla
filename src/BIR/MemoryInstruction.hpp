
#ifndef __MemoryInstruction_h__
#define __MemoryInstruction_h__

#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class MemoryInstruction;
} // namespace BIR

namespace BIR
{
class MemoryInstruction : public BIR::Instruction
{
public:
	string variableName;

public:
	void load(pt::ptree p_) {}
	pt::ptree dump() {}
	void load2(map<int, BIR::Instruction *> instr_list) {}

	virtual string to_bin() = 0;
	virtual string to_str() = 0;
};
} // namespace BIR

#endif
