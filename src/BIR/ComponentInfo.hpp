#include <exception>
using namespace std;

#ifndef __ComponentInfo_h__
#define __ComponentInfo_h__

#include <string>
#include "ComponentType.hpp"
#include "../VIR/Coordinate.hpp"

using namespace std;

namespace BIR
{
class ComponentInfo;
namespace BIREnumerations
{
// enum ComponentType;
}
} // namespace BIR
namespace VIR
{
class Coordinate;
}

namespace BIR
{
class ComponentInfo
{
public:
	BIR::BIREnumerations::ComponentType type;
	int portNo;
	VIR::Coordinate cellCoordinate;
	int statementNo;

public:
	ComponentInfo(const BIR::BIREnumerations::ComponentType type_, const int portNo_, const VIR::Coordinate &cellCoordinate_, int statementNo_);
	ComponentInfo();
	string to_string();
};
} // namespace BIR

#endif
