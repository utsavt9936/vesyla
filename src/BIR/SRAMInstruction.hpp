
#ifndef __SRAMInstruction_h__
#define __SRAMInstruction_h__

#include "ValueWithStaticFlag.hpp"
// #include "RefiInstruction.hpp"
// #include "RouteInstruction.hpp"
#include "MemoryInstruction.hpp"

namespace BIR
{
class ValueWithStaticFlag;
class RefiInstruction;
class RouteInstruction;
// class MemoryInstruction;
class SRAMInstruction;
} // namespace BIR

namespace BIR
{
class SRAMInstruction : public BIR::MemoryInstruction
{
public:
	BIR::ValueWithStaticFlag initialAddress;
	BIR::ValueWithStaticFlag initialDelay;
	BIR::ValueWithStaticFlag loop1Iterations;
	int loop1Increment;
	BIR::ValueWithStaticFlag loop1Delay;
	BIR::ValueWithStaticFlag loop2Iterations;
	BIR::ValueWithStaticFlag loop2Delay;
	int loop2Increment;
	bool isRead;
	int executionCycle;
	int hopNumber;
	BIR::RefiInstruction *correspondingRefiInst;
	BIR::RouteInstruction *correspondingRouteInst;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
