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

#include <string>
using namespace std;

#include "RegFileInstruction.hpp"
#include "Instruction.hpp"

namespace BIR
{


pt::ptree RegFileInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind",kindStr());

        p.put("isDimarchMode",isDimarchMode);
        p.put("pureVariableName",pureVariableName);
        p.put("variableName",variableName);


	vector<string>::iterator it;
	int i = 0;
	for(it = labels.begin(); it != labels.end(); it++,i++)
	{
		pt::ptree pi;
		pi.put("order",i);
		pi.put("tag",*it);
		pd.add_child("label",pi);
	}
	p.add_child("labels", pd);

	return p;
}

void RegFileInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

        isDimarchMode= p.get<bool>("isDimarchMode");
        pureVariableName= p.get<string>("pureVariableName");
        variableName= p.get<string>("variableName");


	string arr[3]={""};
	for (pt::ptree::value_type &v : p.get_child("labels"))
	{
		if(v.first=="label")
		{
			int order = v.second.get<int>("order");
			string tag = v.second.get<string>("tag");
			arr[order] = tag;
		}
	}

	for(int i=0; i<3; i++)
	{
		if(arr[i]!="")
		{
			labels.push_back(arr[i]);	
		}
		else
		{
			break;
		}
	}

}


}
