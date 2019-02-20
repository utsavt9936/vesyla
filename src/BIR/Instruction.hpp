#include <exception>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <bitset>

namespace pt = boost::property_tree;
using namespace std;

#ifndef __Instruction_h__
#define __Instruction_h__

#include "BIRBase.hpp"

namespace BIR
{
// class BIRBase;
class Instruction;
} // namespace BIR

namespace BIR
{
class Instruction : public BIR::BIRBase
{
public:
	int index;
	bool isInResSharingRegion;
	int statementNo;
	int twinStatementNo;
	string unrolledStatementNo;
	int minScheduledClkCycle;
	int maxScheduledClkCycle;
	int offset;
	bool isVector;
	vector<int> exec_trace;

	vector<string> labels;
	int issue_time;
	int arrive_time;
	int activation_time;
	int end_time;

public:
	Instruction();

public:
	virtual ~Instruction() = 0;

public:
	virtual void load(pt::ptree p_) = 0;
	virtual pt::ptree dump() = 0;
	virtual void load2(map<int, BIR::Instruction *> instr_list) = 0;
	virtual string to_bin() = 0;
	virtual string to_str() = 0;
};
} // namespace BIR

#endif
