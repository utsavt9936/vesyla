#include <exception>
using namespace std;

#ifndef __Expression_h__
#define __Expression_h__

#include "VIRBase.hpp"

namespace VIR
{
// class VIRBase;
class Expression;
} // namespace VIR

namespace VIR
{
class Expression : public VIR::VIRBase
{

public:
	virtual ~Expression() = 0;
};
} // namespace VIR

#endif
