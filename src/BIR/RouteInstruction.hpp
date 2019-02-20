
#ifndef __RouteInstruction_h__
#define __RouteInstruction_h__

#include "MemoryInstruction.hpp"
#include "../VIR/Coordinate.hpp"

namespace BIR
{
// class MemoryInstruction;
class RouteInstruction;
} // namespace BIR
namespace VIR
{
class Coordinate;
}

namespace BIR
{
class RouteInstruction : public BIR::MemoryInstruction
{
public:
	int drraSelect;
	bool isFromSource;
	VIR::Coordinate sourceCoordinate;
	VIR::Coordinate destCoordinate;

public:
	void load(pt::ptree p_);
	void load2(map<int, BIR::Instruction *> instr_list) {}
	pt::ptree dump();
	string to_bin();
	string to_str();
};
} // namespace BIR

#endif
