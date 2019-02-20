#include <exception>
using namespace std;

#ifndef __Unrolling_h__
#define __Unrolling_h__

#include "util/Common.hpp"

namespace VIR
{
class Unrolling;
}

namespace VIR
{
class Unrolling
{
public:
	int numberOfRepetitions;

public:
	int unrollingOffset;

public:
	bool isDynamic;

public:
	Unrolling();
};
} // namespace VIR

#endif
