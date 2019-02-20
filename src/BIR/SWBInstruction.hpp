#include <string>
using namespace std;

#ifndef __SWBInstruction_h__
#define __SWBInstruction_h__

#include "ComponentInfo.hpp"
#include "Instruction.hpp"

namespace BIR
{
class ComponentInfo;
// class Instruction;
class SWBInstruction;
} // namespace BIR

namespace BIR
{
class SWBInstruction : public BIR::Instruction
{
public:
	string variableName;
	BIR::ComponentInfo source;
	BIR::ComponentInfo destination;
	BIR::SWBInstruction *dependentTo;
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list);
	pt::ptree dump();

	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
