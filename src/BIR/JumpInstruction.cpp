
#include "JumpInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{

pt::ptree JumpInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("jump_pc", jump_pc);
	if (jumpAddressInstruction)
		p.put("jumpAddressInstruction", jumpAddressInstruction->id());

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

void JumpInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	jump_pc = p.get<int>("jump_pc");

	opt_child = p.get_child_optional("jumpAddressInstruction");
	if (opt_child)
	{
		jumpAddressInstruction = (Instruction *)p.get<int>("jumpAddressInstruction");
	}
	else
	{
		jumpAddressInstruction = NULL;
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

void JumpInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (jumpAddressInstruction)
	{
		intptr_t index = reinterpret_cast<intptr_t>(jumpAddressInstruction);
		jumpAddressInstruction = instr_list[index];
	}
}

string JumpInstruction::to_bin()
{
	string instr_code = "0110";
	string jump_addr = std::bitset<6>(jump_pc).to_string();
	string unused = std::bitset<17>(jump_pc).to_string();
	string instr_bin = instr_code + jump_addr + unused;
	return instr_bin;
}

string JumpInstruction::to_str()
{
	string instr_code = "JUMP";
	string jump_addr = to_string(jump_pc);
	string instr_manas = instr_code + " " + jump_addr;
	return instr_manas;
}

} // namespace BIR
