#ifndef __Integer_h__
#define __Integer_h__

#include "Scalar.hpp"

namespace VIR
{
// class Scalar;
class Integer;
} // namespace VIR

namespace VIR
{
class Integer : public VIR::Scalar
{
public:
	int value;
};
} // namespace VIR

#endif
