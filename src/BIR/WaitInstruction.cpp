// Copyright (C) 2019 Yu Yang
// 
// This file is part of Vesyla.
// 
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.


#include "WaitInstruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "Instruction.hpp"

namespace BIR
{

pt::ptree WaitInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("numCycles", numberOfCycles.value);
	p.put("numCyclesFlag", numberOfCycles.isStatic);

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

void WaitInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");
	numberOfCycles(p.get<int>("numCycles"), p.get<bool>("numCyclesFlag"));

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

string WaitInstruction::to_bin()
{
	string instr = "0111";
	instr += std::bitset<1>((int)!numberOfCycles.isStatic).to_string();
	instr += std::bitset<15>(numberOfCycles.value).to_string();
	instr += std::bitset<27 - 4 - 1 - 15>(0).to_string();
	return instr;
}

string WaitInstruction::to_str()
{
	string instr = "DELAY";
	instr += " " + to_string((int)!numberOfCycles.isStatic);
	instr += " " + to_string(numberOfCycles.value);
	return instr;
}

} // namespace BIR
