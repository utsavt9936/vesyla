#include <vector>
using namespace std;

#ifndef __LoopHeaderInstruction_h__
#define __LoopHeaderInstruction_h__

// #include "LoopTailInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{
class LoopTailInstruction;
// class Instruction;
class LoopHeaderInstruction;
} // namespace BIR

namespace BIR
{
class LoopHeaderInstruction : public BIR::Instruction
{
public:
	int loopId;
	int startValue;
	bool isStatic;
	int iterationNumber;
	BIR::LoopTailInstruction *correspondingLoopTailInst;
	BIR::LoopHeaderInstruction *upperLoop;
	vector<BIR::LoopHeaderInstruction *> innerLoops;
	int loopExecution;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
