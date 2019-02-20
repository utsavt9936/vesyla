#include <exception>
using namespace std;

#ifndef __Initialization_h__
#define __Initialization_h__

#include "VIRBase.hpp"

namespace VIR
{
// class VIRBase;
class Initialization;
} // namespace VIR

namespace VIR
{
class Initialization : public VIR::VIRBase
{

public:
	virtual ~Initialization() = 0;
};
} // namespace VIR

#endif
