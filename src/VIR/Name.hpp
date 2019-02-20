#include <exception>
using namespace std;

#ifndef __Name_h__
#define __Name_h__

#include "Expression.hpp"

namespace VIR {
// class Expression;
class Name;
}

namespace VIR {
class Name: public VIR::Expression {
private:
	bool _isDummy;
public:
	Expression* reverse_bits;

public:
	Name();

public:
	virtual ~Name() = 0;

public:
	bool isDummy() const;

public:
	void isDummy(bool isDummy_);
};
}

#endif
