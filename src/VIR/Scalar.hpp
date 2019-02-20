#include <exception>
using namespace std;

#ifndef __Scalar_h__
#define __Scalar_h__

#include "NumericLiteral.hpp"

namespace VIR
{
// class NumericLiteral;
class Scalar;
} // namespace VIR

namespace VIR
{
class Scalar : public VIR::NumericLiteral
{

public:
	virtual ~Scalar() = 0;
};
} // namespace VIR

#endif
