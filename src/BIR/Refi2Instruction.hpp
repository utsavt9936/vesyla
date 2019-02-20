
#ifndef __Refi2Instruction_h__
#define __Refi2Instruction_h__

#include "ValueWithStaticFlag.hpp"
#include "RegFileInstruction.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class RegFileInstruction;
class Refi2Instruction;
} // namespace BIR

namespace BIR
{
class Refi2Instruction : public BIR::RegFileInstruction
{
public:
	BIR::ValueWithStaticFlag middleDelay;
	BIR::ValueWithStaticFlag numberOfRepetition;
	int repetitionOffset;
	BIR::ValueWithStaticFlag stepValue;

public:
	void load(pt::ptree p_) {}
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump() {}

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
