#include <exception>
using namespace std;

#ifndef __AddressInfo_h__
#define __AddressInfo_h__

#include "util/Common.hpp"
#include "Identifier.hpp"

// #include "ForStatement.hpp"

namespace VIR
{
class ForStatement;
class AddressInfo;
} // namespace VIR

namespace VIR
{
class AddressInfo
{
public:
	int startAddress;
	int increment;
	int numberOfAddress;
	int numberOfRepetitions;
	int repetitionOffset;
	bool is1stLevelDynamic;
	bool is2ndLevelDynamic;
	VIR::ForStatement *firstLevelLoop;
	VIR::ForStatement *secondLevelLoop;

public:
	AddressInfo();
};
} // namespace VIR

#endif
