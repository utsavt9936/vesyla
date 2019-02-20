#include <exception>
using namespace std;

#ifndef __Literal_h__
#define __Literal_h__

#include "Expression.hpp"

namespace VIR
{
// class Expression;
class Literal;
} // namespace VIR

namespace VIR
{
class Literal : public VIR::Expression
{

public:
	virtual ~Literal() = 0;
};
} // namespace VIR

#endif
