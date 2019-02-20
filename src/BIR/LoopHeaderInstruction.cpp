#include <vector>
using namespace std;

#include "LoopHeaderInstruction.hpp"
#include "LoopTailInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{

pt::ptree LoopHeaderInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("loopId", loopId);
	p.put("startValue", startValue);
	p.put("isStatic", isStatic);

	p.put("iterationNumber", iterationNumber);

	if (correspondingLoopTailInst)
		p.put("correspondingLoopTailInst", correspondingLoopTailInst->id());

	if (upperLoop)
		p.put("upperLoop", upperLoop->id());

	vector<BIR::LoopHeaderInstruction *>::iterator innerLoopIt;
	pt::ptree innerLoopTree;
	for (innerLoopIt = innerLoops.begin(); innerLoopIt != innerLoops.end(); innerLoopIt++)
	{
		pt::ptree pi;
		pi.put("Id", (*innerLoopIt)->id());
		innerLoopTree.add_child("innerLoop", pi);
	}
	p.add_child("innerLoops", innerLoopTree);

	p.put("loopExecution", loopExecution);

	vector<string>::iterator it;
	int i = 0;
	for (it = labels.begin(); it != labels.end(); it++, i++)
	{
		pt::ptree pi;
		pi.put("order", i);
		pi.put("tag", *it);
		pd.add_child("label", pi);
	}
	p.add_child("labels", pd);

	return p;
}

void LoopHeaderInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	loopId = p.get<int>("loopId");
	startValue = p.get<int>("startValue");
	isStatic = p.get<bool>("isStatic");
	iterationNumber = p.get<int>("iterationNumber");

	opt_child = p.get_child_optional("correspondingLoopTailInst");
	if (opt_child)
	{
		correspondingLoopTailInst = (BIR::LoopTailInstruction *)p.get<int>("correspondingLoopTailInst");
	}
	else
	{
		correspondingLoopTailInst = NULL;
	}

	opt_child = p.get_child_optional("upperLoop");
	if (opt_child)
	{
		upperLoop = (BIR::LoopHeaderInstruction *)p.get<int>("upperLoop");
	}
	else
	{
		upperLoop = NULL;
	}

	for (pt::ptree::value_type &v : p.get_child("innerLoops"))
	{
		if (v.first == "innerLoop")
		{
			innerLoops.push_back((BIR::LoopHeaderInstruction *)v.second.get<int>("Id"));
		}
	}

	loopExecution = p.get<int>("loopExecution");

	string arr[3] = {""};
	for (pt::ptree::value_type &v : p.get_child("labels"))
	{
		if (v.first == "label")
		{
			int order = v.second.get<int>("order");
			string tag = v.second.get<string>("tag");
			arr[order] = tag;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (arr[i] != "")
		{
			labels.push_back(arr[i]);
		}
		else
		{
			break;
		}
	}
}

void LoopHeaderInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (correspondingLoopTailInst)
	{
		intptr_t index = reinterpret_cast<intptr_t>(correspondingLoopTailInst);
		correspondingLoopTailInst = (LoopTailInstruction *)instr_list[index];
	}

	if (upperLoop)
	{
		index = reinterpret_cast<intptr_t>(upperLoop);
		upperLoop = (LoopHeaderInstruction *)instr_list[index];
	}

	int i = 0;
	vector<BIR::LoopHeaderInstruction *>::iterator it;
	for (it = innerLoops.begin(); it != innerLoops.end(); it++, i++)
	{
		index = reinterpret_cast<intptr_t>(*it);
		if (index)
		{
			innerLoops[i] = (BIR::LoopHeaderInstruction *)(instr_list[index]);
		}
		else
		{
			innerLoops[i] = NULL;
		}
	}
}

string LoopHeaderInstruction::to_bin()
{
	string instr = "1000";
	instr += std::bitset<4>(loopId).to_string();
	instr += std::bitset<6>(startValue).to_string();
	instr += std::bitset<1>(isStatic ? 0 : 1).to_string();
	instr += std::bitset<6>(iterationNumber).to_string();
	instr += std::bitset<27 - 4 - 4 - 6 - 1 - 6 - 6>(0).to_string();
	return instr;
}

string LoopHeaderInstruction::to_str()
{
	string instr = "LOOPH";
	instr += " " + to_string(loopId);
	instr += " " + to_string(startValue);
	instr += " " + to_string(isStatic ? 0 : 1);
	instr += " " + to_string(iterationNumber);
	return instr;
}

} // namespace BIR
