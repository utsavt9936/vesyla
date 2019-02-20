
#ifndef __Refi3Instruction_h__
#define __Refi3Instruction_h__

#include "ValueWithStaticFlag.hpp"
#include "RegFileInstruction.hpp"
#include "AddressMode.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class RegFileInstruction;
class Refi3Instruction;
namespace BIREnumerations
{
// enum AddressMode;
}
} // namespace BIR

namespace BIR
{
class Refi3Instruction : public BIR::RegFileInstruction
{
public:
	int middleDelayExt;
	int numberOfRepetitionExt;
	BIR::ValueWithStaticFlag repetitionDelay;
	int repetitionOffsetExt;
	BIR::BIREnumerations::AddressMode addressMode;
	BIR::ValueWithStaticFlag reverse_bits;

public:
	void load(pt::ptree p_) {}
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump() {}

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
