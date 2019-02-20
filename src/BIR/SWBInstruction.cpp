#include <string>
using namespace std;

#include "SWBInstruction.hpp"
#include "ComponentInfo.hpp"
#include "Instruction.hpp"

namespace BIR
{

pt::ptree SWBInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("variableName", variableName);

	p.put("source_type", source.type);
	p.put("source_portNo", source.portNo);
	p.put("source_cell_row", source.cellCoordinate.row);
	p.put("source_cell_col", source.cellCoordinate.column);
	p.put("source_cell_bank", source.cellCoordinate.bank);
	p.put("source_stmtNo", source.statementNo);

	p.put("destination_type", destination.type);
	p.put("destination_portNo", destination.portNo);
	p.put("destination_cell_row", destination.cellCoordinate.row);
	p.put("destination_cell_col", destination.cellCoordinate.column);
	p.put("destination_cell_bank", destination.cellCoordinate.bank);
	p.put("destination_stmtNo", destination.statementNo);

	//instruction id of the node pointed by dependentTo ptr
	if (dependentTo)
	{
		p.put("dependentTo", dependentTo->id());
	}

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

void SWBInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");
	variableName = p.get<string>("variableName");

	source.type = (BIREnumerations::ComponentType)(p.get<int>("source_type"));
	source.portNo = p.get<int>("source_portNo");
	source.cellCoordinate.row = p.get<int>("source_cell_row");
	source.cellCoordinate.column = p.get<int>("source_cell_col");
	source.cellCoordinate.bank = p.get<int>("source_cell_bank");
	source.statementNo = p.get<int>("source_stmtNo");

	destination.type = (BIREnumerations::ComponentType)(p.get<int>("destination_type"));
	destination.portNo = p.get<int>("destination_portNo");
	destination.cellCoordinate.row = p.get<int>("destination_cell_row");
	destination.cellCoordinate.column = p.get<int>("destination_cell_col");
	destination.cellCoordinate.bank = p.get<int>("destination_cell_bank");
	destination.statementNo = p.get<int>("destination_stmtNo");

	opt_child = p.get_child_optional("dependentTo");
	if (opt_child)
	{
		//int inst_id = p.get<int>("dependentTo");
		dependentTo = (BIR::SWBInstruction *)p.get<int>("dependentTo");
	}
	else
	{
		dependentTo = NULL;
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

void SWBInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	if (dependentTo != NULL)
	{
		intptr_t index = reinterpret_cast<intptr_t>(dependentTo);
		dependentTo = (BIR::SWBInstruction *)instr_list[index];
	}
}

string SWBInstruction::to_bin()
{
	ComponentInfo componentInfo_src;
	ComponentInfo componentInfo_dest;
	componentInfo_src = source;
	componentInfo_dest = destination;

	__NOT_IMPLEMENTED__;
}

string SWBInstruction::to_str()
{
	__NOT_IMPLEMENTED__;
}

} // namespace BIR
