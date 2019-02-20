
#include "LoopTailInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{

pt::ptree LoopTailInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("loopId", loopId);
	p.put("stepValue", stepValue);
	p.put("gotoPC", gotoPC);

	if (corresponding_loop_header_instr)
		p.put("corresponding_loop_header_instr", corresponding_loop_header_instr->id());

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

void LoopTailInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	loopId = p.get<int>("loopId");
	stepValue = p.get<int>("stepValue");
	gotoPC = p.get<int>("gotoPC");

	opt_child = p.get_child_optional("corresponding_loop_header_instr");
	if (opt_child)
	{
		corresponding_loop_header_instr = (Instruction *)p.get<int>("corresponding_loop_header_instr");
	}
	else
	{
		corresponding_loop_header_instr = NULL;
	}

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

void LoopTailInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (corresponding_loop_header_instr)
	{
		intptr_t index1 = reinterpret_cast<intptr_t>(corresponding_loop_header_instr);
		corresponding_loop_header_instr = (Instruction *)instr_list[index1];
	}
}

string LoopTailInstruction::to_bin()
{
	string instr = "1001";
	instr += std::bitset<4>(stepValue).to_string();
	instr += std::bitset<6>(gotoPC).to_string();
	instr += std::bitset<6>(loopId).to_string();
	instr += std::bitset<27 - 4 - 4 - 6 - 6>(0).to_string();
	return instr;
}

string LoopTailInstruction::to_str()
{
	string instr = "LOOPH";
	instr += " " + to_string(stepValue);
	instr += " " + to_string(gotoPC);
	instr += " " + to_string(loopId);
	return instr;
}

} // namespace BIR
