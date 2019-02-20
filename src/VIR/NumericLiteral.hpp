#include <exception>
using namespace std;

#ifndef __NumericLiteral_h__
#define __NumericLiteral_h__

#include "Literal.hpp"

namespace VIR {
// class Literal;
class NumericLiteral;
}

namespace VIR {
class NumericLiteral: public VIR::Literal {

public:
	virtual ~NumericLiteral() = 0;
};
}

#endif
