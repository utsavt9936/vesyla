#include <exception>
using namespace std;

#ifndef __Statement_h__
#define __Statement_h__

#include "VIRBase.hpp"

namespace VIR {
// class VIRBase;
class Statement;
}

namespace VIR {
class Statement: public VIR::VIRBase {
private:
	VIR::Statement * _controlDependentTo;
private:
	int _statementNo;

public:
	Statement();

public:
	virtual ~Statement() = 0;

public:
	VIR::Statement * controlDependentTo() const;

public:
	void controlDependentTo(VIR::Statement * controlDependentTo_);

public:
	int statementNo() const;

public:
	void statementNo(int statementNo_);
};
}

#endif
