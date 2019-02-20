#ifndef __FloatingPoint_h__
#define __FloatingPoint_h__

#include "Scalar.hpp"

namespace VIR
{
// class Scalar;
class FloatingPoint;
} // namespace VIR

namespace VIR
{
class FloatingPoint : public VIR::Scalar
{
public:
	float value;
};
} // namespace VIR

#endif
