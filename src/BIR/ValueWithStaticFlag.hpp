#include <exception>
using namespace std;

#ifndef __ValueWithStaticFlag_h__
#define __ValueWithStaticFlag_h__

#include "util/Common.hpp"

namespace BIR
{
class ValueWithStaticFlag;
}

namespace BIR
{
class ValueWithStaticFlag
{
public:
	int value;

public:
	bool isStatic;

public:
	void operator()(int value_, bool isStatic_);
};
} // namespace BIR

#endif
