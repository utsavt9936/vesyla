#include <exception>
using namespace std;

#ifndef __ControlStatement_h__
#define __ControlStatement_h__

#include "Statement.hpp"

namespace VIR
{
// class Statement;
class ControlStatement;
} // namespace VIR

namespace VIR
{
class ControlStatement : public Statement
{
public:
	virtual ~ControlStatement() = 0;
};
} // namespace VIR

#endif
