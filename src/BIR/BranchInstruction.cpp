
#include "BranchInstruction.hpp"
#include "Instruction.hpp"
#include "BranchMode.hpp"

namespace BIR
{

pt::ptree BranchInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("mode", mode);
	p.put("modeValue", modeValue);

	if (falseAddressInstruction)
	{
		p.put("falseAddressInstruction", falseAddressInstruction->id());
	}
	p.put("false_pc", false_pc);

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

void BranchInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	mode = (BIR::BIREnumerations::BranchMode)p.get<int>("mode");
	modeValue = p.get<int>("modeValue");

	opt_child = p.get_child_optional("falseAddressInstruction");
	if (opt_child)
	{
		falseAddressInstruction = (BIR::Instruction *)p.get<int>("falseAddressInstruction");
	}
	else
	{
		falseAddressInstruction = NULL;
	}

	false_pc = p.get<int>("false_pc");

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

void BranchInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (falseAddressInstruction)
	{
		intptr_t index = reinterpret_cast<intptr_t>(falseAddressInstruction);
		falseAddressInstruction = instr_list[index];
	}
}

string BranchInstruction::to_bin()
{
	string instr = "1011";
	instr += std::bitset<2>(modeValue).to_string();
	instr += std::bitset<6>(false_pc).to_string();
	instr += std::bitset<27 - 4 - 2 - 6>(0).to_string();
	return instr;
}

string BranchInstruction::to_str()
{
	string instr = "BRANCH";
	string modestr = "";
	switch (modeValue)
	{
	case 0:
		modestr = "GR";
		break;
	case 1:
		modestr = "GE";
		break;
	case 2:
		modestr = "EQ";
		break;
	default:
		LOG(FATAL) << "Illegal branch mode: " << modeValue;
	}
	instr += " " + modestr;
	instr += " " + to_string(false_pc);
	return instr;
}

} // namespace BIR
