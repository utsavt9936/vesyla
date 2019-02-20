
#ifndef __LoopTailInstruction_h__
#define __LoopTailInstruction_h__

#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class LoopTailInstruction;
} // namespace BIR

namespace BIR
{
class LoopTailInstruction : public BIR::Instruction
{
public:
	int loopId;
	int stepValue;
	int gotoPC;
	Instruction *corresponding_loop_header_instr;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
