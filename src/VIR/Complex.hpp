#ifndef __Complex_h__
#define __Complex_h__

#include "Scalar.hpp"

namespace VIR
{
// class Scalar;
class Complex;
} // namespace VIR

namespace VIR
{
class Complex : public VIR::Scalar
{
public:
	double rValue;

public:
	double iValue;
};
} // namespace VIR

#endif
