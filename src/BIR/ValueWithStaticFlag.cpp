#include <exception>
using namespace std;

#include "ValueWithStaticFlag.hpp"

void BIR::ValueWithStaticFlag::operator()(int value_, bool isStatic_)
{
	value = value_;
	isStatic = isStatic_;
}

