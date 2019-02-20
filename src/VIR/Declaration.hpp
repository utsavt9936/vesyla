#include <exception>
using namespace std;

#ifndef __Declaration_h__
#define __Declaration_h__

#include "VIRBase.hpp"

namespace VIR
{
// class VIRBase;
class Declaration;
} // namespace VIR

namespace VIR
{
class Declaration : public VIR::VIRBase
{

public:
	virtual ~Declaration() = 0;
};
} // namespace VIR

#endif
