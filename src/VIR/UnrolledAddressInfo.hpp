#ifndef __UnrolledAddressInfo_h__
#define __UnrolledAddressInfo_h__

#include "util/Common.hpp"

namespace VIR
{
class UnrolledAddressInfo;
}

namespace VIR
{
class UnrolledAddressInfo
{
public:
	int startAddress;

public:
	int increment;

public:
	int numberOfAddress;

public:
	int numberOfRepetitions;

public:
	int repetitionOffset;
};
} // namespace VIR

#endif
