#include <exception>
using namespace std;

#ifndef __Pragma_h__
#define __Pragma_h__

#include "VIRBase.hpp"

namespace VIR
{
// class VIRBase;
class Pragma;
} // namespace VIR

namespace VIR
{
class Pragma : public VIR::VIRBase
{

public:
	virtual ~Pragma() = 0;
};
} // namespace VIR

#endif
