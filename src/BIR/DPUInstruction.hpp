
#include <vector>
using namespace std;

#ifndef __DPUInstruction_h__
#define __DPUInstruction_h__

// #include "RefiInstruction.hpp"
// #include "SWBInstruction.hpp"
#include "Instruction.hpp"
//#include "DPUMode.hpp"
#include "DpuIOChange.hpp"
#include "DpuParameterType.hpp"

namespace BIR
{
class RefiInstruction;
class SWBInstruction;
// class Instruction;
class DPUInstruction;
namespace BIREnumerations
{
// enum DPUMode;
// enum DpuIOChange;
}
} // namespace BIR

namespace BIR
{
class DPUInstruction : public BIR::Instruction
{
public:
	string mode;
	int modeValue;
	int executionCycle;
	int repetition;
	vector<BIR::DPUInstruction *> correspondingChainedDpus;
	vector<BIR::RefiInstruction *> correspondingRefiInsts;
	vector<BIR::SWBInstruction *> correspondingSWBInsts;
	BIR::BIREnumerations::DpuIOChange ioChange;
	int constantValue;
	int int_imm_data;
	float float_imm_data;
	bool saturation;
	bool fixedPointMode;
	BIR::BIREnumerations::DpuParameterType parameter_type;
	bool reductive;

public:
	void load(pt::ptree p_);
	pt::ptree dump();
	void load2(map<int, BIR::Instruction *> instr_list);

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
