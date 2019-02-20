#include <exception>
using namespace std;

#ifndef __AssignmentPragma_h__
#define __AssignmentPragma_h__

#include "Pragma.hpp"

namespace VIR
{
// class Pragma;
class AssignmentPragma;
} // namespace VIR

namespace VIR
{
class AssignmentPragma : public VIR::Pragma
{

public:
	virtual ~AssignmentPragma() = 0;
};
} // namespace VIR

#endif
