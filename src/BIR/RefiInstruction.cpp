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

#include <vector>
using namespace std;

#include "RefiInstruction.hpp"
#include "ValueWithStaticFlag.hpp"
#include "SWBInstruction.hpp"
#include "DPUInstruction.hpp"
#include "RegFileInstruction.hpp"
#include "AddressMode.hpp"
#include "PortMode.hpp"

namespace BIR
{

pt::ptree RefiInstruction::dump()
{
	pt::ptree p;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("initialDelayValue", initialDelay.value);
	p.put("initialDelayFlag", initialDelay.isStatic);

	p.put("middleDelayValue", middleDelay.value);
	p.put("middleDelayFlag", middleDelay.isStatic);

	p.put("numberOfAddressValue", numberOfAddress.value);
	p.put("numberOfAddressFlag", numberOfAddress.isStatic);

	p.put("numberOfRepetitionValue", numberOfRepetition.value);
	p.put("numberOfRepetitionFlag", numberOfRepetition.isStatic);

	p.put("portNo", portNo);

	p.put("repetitionDelayValue", repetitionDelay.value);
	p.put("repetitionDelayFlag", repetitionDelay.isStatic);

	p.put("repetitionOffset", repetitionOffset);

	p.put("startAddressValue", startAddress.value);
	p.put("startAddressFlag", startAddress.isStatic);

	p.put("stepValueValue", stepValue.value);
	p.put("stepValueFlag", stepValue.isStatic);

	p.put("addressMode", addressMode);
	p.put("portMode", portMode);

	vector<BIR::SWBInstruction *>::iterator swbIt;
	pt::ptree swbTree;
	for (swbIt = correspondingSWBInsts.begin(); swbIt != correspondingSWBInsts.end(); swbIt++)
	{
		pt::ptree pi;
		pi.put("Id", (*swbIt)->id());
		swbTree.add_child("SWBInst", pi);
	}
	p.add_child("correspondingSWBInsts", swbTree);

	if (dependentTo)
	{
		p.put("dependentTo", dependentTo->id());
	}

	p.put("reverse_bitsValue", reverse_bits.value);
	p.put("reverse_bitsFlag", reverse_bits.isStatic);

	if (correspondingDpuInst)
	{
		p.put("correspondingDpuInst", correspondingDpuInst->id());
	}
	if (correspondingRefiTransferInst)
	{
		p.put("correspondingRefiTransferInst", correspondingRefiTransferInst->id());
	}
	p.put("bankNo", bankNo);

	pt::ptree pd;
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

void RefiInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	initialDelay(p.get<int>("initialDelayValue"), p.get<bool>("initialDelayFlag"));
	middleDelay(p.get<int>("middleDelayValue"), p.get<bool>("middleDelayFlag"));
	numberOfAddress(p.get<int>("numberOfAddressValue"), p.get<bool>("numberOfAddressFlag"));
	numberOfRepetition(p.get<int>("numberOfRepetitionValue"), p.get<bool>("numberOfRepetitionFlag"));
	portNo = p.get<int>("portNo");
	repetitionDelay(p.get<int>("repetitionDelayValue"), p.get<bool>("repetitionDelayFlag"));
	repetitionOffset = p.get<int>("repetitionOffset");
	startAddress(p.get<int>("startAddressValue"), p.get<bool>("startAddressFlag"));
	stepValue(p.get<int>("stepValueValue"), p.get<bool>("stepValueFlag"));
	addressMode = (BIREnumerations::AddressMode)p.get<int>("addressMode");
	portMode = (BIREnumerations::PortMode)p.get<int>("portMode");

	for (pt::ptree::value_type &v : p.get_child("correspondingSWBInsts"))
	{
		if (v.first == "SWBInst")
		{
			correspondingSWBInsts.push_back((BIR::SWBInstruction *)v.second.get<int>("Id"));
		}
	}

	opt_child = p.get_child_optional("dependentTo");
	if (opt_child)
	{
		dependentTo = (BIR::RefiInstruction *)p.get<int>("dependentTo");
	}
	else
	{
		dependentTo = NULL;
	}
	reverse_bits(p.get<int>("reverse_bitsValue"), p.get<bool>("reverse_bitsFlag"));
	opt_child = p.get_child_optional("correspondingDpuInst");
	if (opt_child)
	{
		correspondingDpuInst = (BIR::DPUInstruction *)p.get<int>("correspondingDpuInst");
	}
	else
	{
		correspondingDpuInst = NULL;
	}
	opt_child = p.get_child_optional("correspondingRefiTransferInst");
	if (opt_child)
	{
		correspondingRefiTransferInst = (BIR::RefiInstruction *)p.get<int>("correspondingRefiTransferInst");
	}
	else
	{
		correspondingRefiTransferInst = NULL;
	}
	bankNo = p.get<int>("bankNo");

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

void RefiInstruction::load2(map<int, BIR::Instruction *> instr_list)
{
	intptr_t index;
	int i = 0;
	vector<BIR::SWBInstruction *>::iterator swbIt;

	for (swbIt = correspondingSWBInsts.begin(); swbIt != correspondingSWBInsts.end(); swbIt++, i++)
	{
		index = reinterpret_cast<intptr_t>(*swbIt);
		if (index)
		{
			correspondingSWBInsts[i] = (BIR::SWBInstruction *)(instr_list[index]);
		}
		else
		{
			correspondingSWBInsts[i] = NULL;
		}
	}

	index = reinterpret_cast<intptr_t>(dependentTo);
	if (index)
	{
		dependentTo = (BIR::RefiInstruction *)instr_list[index];
	}
	else
	{
		dependentTo = NULL;
	}

	index = reinterpret_cast<intptr_t>(correspondingDpuInst);
	if (index)
	{
		correspondingDpuInst = (BIR::DPUInstruction *)instr_list[index];
	}
	else
	{
		correspondingDpuInst = NULL;
	}

	index = reinterpret_cast<intptr_t>(correspondingRefiTransferInst);
	if (index)
	{
		correspondingRefiTransferInst = (BIR::RefiInstruction *)instr_list[index];
	}
	else
	{
		correspondingRefiTransferInst = NULL;
	}
}

} // namespace BIR
