
#include "RouteInstruction.hpp"
#include "MemoryInstruction.hpp"
#include "../VIR/Coordinate.hpp"

namespace BIR
{

pt::ptree RouteInstruction::dump()
{
	pt::ptree p;
	pt::ptree pd;

	p.put("id", id());
	p.put("kind", kindStr());

	p.put("drraSelect", drraSelect);
	p.put("isFromSource", isFromSource);

	p.put("srcRow", sourceCoordinate.row);
	p.put("srcCol", sourceCoordinate.column);
	p.put("srcBank", sourceCoordinate.bank);

	p.put("destRow", destCoordinate.row);
	p.put("destCol", destCoordinate.column);
	p.put("destBank", destCoordinate.bank);

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

void RouteInstruction::load(pt::ptree p)
{
	boost::optional<const pt::ptree &> opt_child;

	//id(p.get<int>("id"));
	//string kind = p.get<string>("kind");

	drraSelect = p.get<int>("drraSelect");
	isFromSource = p.get<bool>("isFromSource");
	sourceCoordinate.row = p.get<int>("srcRow");
	sourceCoordinate.column = p.get<int>("srcCol");
	sourceCoordinate.bank = p.get<int>("srcBank");
	destCoordinate.row = p.get<int>("destRow");
	destCoordinate.column = p.get<int>("destCol");
	destCoordinate.bank = p.get<int>("destBank");

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

string RouteInstruction::to_bin()
{
	__NOT_IMPLEMENTED__;
}
string RouteInstruction::to_str()
{
	__NOT_IMPLEMENTED__;
}

} // namespace BIR
