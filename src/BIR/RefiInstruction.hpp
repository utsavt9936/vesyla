#include <vector>
using namespace std;

#ifndef __RefiInstruction_h__
#define __RefiInstruction_h__

#include "ValueWithStaticFlag.hpp"
// #include "SWBInstruction.hpp"
// #include "DPUInstruction.hpp"
#include "RegFileInstruction.hpp"
#include "AddressMode.hpp"
#include "PortMode.hpp"

namespace BIR
{
class ValueWithStaticFlag;
class SWBInstruction;
class DPUInstruction;
// class RegFileInstruction;
class RefiInstruction;
namespace BIREnumerations
{
// enum AddressMode;
// enum PortMode;
}
} // namespace BIR

namespace BIR
{
class RefiInstruction : public BIR::RegFileInstruction
{
public:
	BIR::ValueWithStaticFlag initialDelay;
	BIR::ValueWithStaticFlag middleDelay;
	BIR::ValueWithStaticFlag numberOfAddress;
	BIR::ValueWithStaticFlag numberOfRepetition;
	int portNo;
	BIR::ValueWithStaticFlag repetitionDelay;
	int repetitionOffset;
	BIR::ValueWithStaticFlag startAddress;
	BIR::ValueWithStaticFlag stepValue;
	BIR::BIREnumerations::AddressMode addressMode;
	BIR::BIREnumerations::PortMode portMode;
	vector<BIR::SWBInstruction *> correspondingSWBInsts;
	BIR::RefiInstruction *dependentTo;
	BIR::ValueWithStaticFlag reverse_bits;
	BIR::DPUInstruction *correspondingDpuInst;
	BIR::RefiInstruction *correspondingRefiTransferInst;
	int bankNo;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin(){};
	string to_str(){};
};
} // namespace BIR

#endif
