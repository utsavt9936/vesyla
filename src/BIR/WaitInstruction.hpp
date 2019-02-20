
#ifndef __WaitInstruction_h__
#define __WaitInstruction_h__

#include "ValueWithStaticFlag.hpp"
#include "Instruction.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class Instruction;
class WaitInstruction;
} // namespace BIR

namespace BIR
{
class WaitInstruction : public BIR::Instruction
{
public:
	BIR::ValueWithStaticFlag numberOfCycles;
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
