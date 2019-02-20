
#ifndef __Refi1Instruction_h__
#define __Refi1Instruction_h__

#include "ValueWithStaticFlag.hpp"
#include "RegFileInstruction.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class RegFileInstruction;
class Refi1Instruction;
} // namespace BIR

namespace BIR
{
class Refi1Instruction : public BIR::RegFileInstruction
{
public:
	BIR::ValueWithStaticFlag initialDelay;
	BIR::ValueWithStaticFlag numberOfAddress;
	int portNo;
	BIR::ValueWithStaticFlag startAddress;
	int numberOfSubseqInst;

public:
	void load(pt::ptree p_) {}
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump() {}

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
