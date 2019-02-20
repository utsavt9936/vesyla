#include <exception>
#include "ComponentInfo.hpp"
#include "ComponentType.hpp"
#include "../VIR/Coordinate.hpp"

BIR::ComponentInfo::ComponentInfo(const BIR::BIREnumerations::ComponentType type_, const int portNo_, const VIR::Coordinate &cellCoordinate_, int statementNo_)
{
	type = type_;
	portNo = portNo_;
	cellCoordinate = cellCoordinate_;
	statementNo = statementNo_;
}

BIR::ComponentInfo::ComponentInfo()
{
}

string BIR::ComponentInfo::to_string()
{
	string s = "";
	s += std::to_string(cellCoordinate.row) + "_" + std::to_string(cellCoordinate.column);
	s += "_";
	if (type == BIR::BIREnumerations::ctDPU)
	{
		s += "DPU";
	}
	else if (type == BIR::BIREnumerations::ctRegFile)
	{
		s += "REG";
	}
	else
	{
		s += "MEM";
	}
	s += "_" + std::to_string(portNo);
	return s;
}
