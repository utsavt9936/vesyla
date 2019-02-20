
#ifndef __RACCUInstruction_h__
#define __RACCUInstruction_h__

#include "ValueWithStaticFlag.hpp"
#include "Instruction.hpp"
#include "RACCUMode.hpp"

namespace BIR
{
class ValueWithStaticFlag;
// class Instruction;
class RACCUInstruction;
namespace BIREnumerations
{
// enum RACCUMode;
}
} // namespace BIR

namespace BIR
{
class RACCUInstruction : public BIR::Instruction
{
public:
	BIR::BIREnumerations::RACCUMode raccuMode;
	BIR::ValueWithStaticFlag operand1;
	BIR::ValueWithStaticFlag operand2;
	int resultAddress;
	BIR::Instruction *dependentTo;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
