#include <string>
using namespace std;

#ifndef __StringLiteral_h__
#define __StringLiteral_h__

#include "Literal.hpp"

namespace VIR
{
// class Literal;
class StringLiteral;
} // namespace VIR

namespace VIR
{
class StringLiteral : public VIR::Literal
{
public:
	string value;
};
} // namespace VIR

#endif
