#include <string>
using namespace std;

#ifndef __RegFileInstruction_h__
#define __RegFileInstruction_h__

#include "Instruction.hpp"

namespace BIR
{
// class Instruction;
class RegFileInstruction;
} // namespace BIR

namespace BIR
{
class RegFileInstruction : public BIR::Instruction
{
public:
	bool isDimarchMode;
	string pureVariableName;
	string variableName;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump();

	string to_bin(){};
	string to_str(){};
};
} // namespace BIR

#endif
