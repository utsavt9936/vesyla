#ifndef __RFILEInstruction_h__
#define __RFILEInstruction_h__

#include "MemoryInstruction.hpp"
#include "AddressMode.hpp"

namespace BIR
{
// class MemoryInstruction;
class RFILEInstruction;
namespace BIREnumerations
{
// enum AddressMode;
}
} // namespace BIR

namespace BIR
{
class RFILEInstruction : public BIR::MemoryInstruction
{
public:
	int initialDelay;
	int middleDelay;
	int startAddress;
	int endAddress;
	int numberOfRepetition;
	int repetitionDelay;
	int repetitionOffset;
	int increment;
	bool isRead;
	int drraRow;
	BIR::BIREnumerations::AddressMode addressMode;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump();

	string to_bin(){};
	string to_str(){};
};
} // namespace BIR

#endif
