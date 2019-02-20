
#ifndef __BranchInstruction_h__
#define __BranchInstruction_h__

#include "Instruction.hpp"
#include "BranchMode.hpp"

namespace BIR
{
// class Instruction;
class BranchInstruction;
namespace BIREnumerations
{
// enum BranchMode;
}
} // namespace BIR

namespace BIR
{
class BranchInstruction : public BIR::Instruction
{
public:
	BIR::BIREnumerations::BranchMode mode;
	int modeValue;
	BIR::Instruction *falseAddressInstruction;
	int false_pc;
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
