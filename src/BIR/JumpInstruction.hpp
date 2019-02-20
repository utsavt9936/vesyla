
#ifndef __JumpInstruction_h__
#define __JumpInstruction_h__

#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class JumpInstruction;
} // namespace BIR

namespace BIR
{

class JumpInstruction : public Instruction
{
public:
	Instruction *jumpAddressInstruction;
	int jump_pc;

public:
	void load(pt::ptree p_);
	pt::ptree dump();
	void load2(map<int, BIR::Instruction *> instr_list);
	string to_bin();
	string to_str();
};

} // namespace BIR

#endif
