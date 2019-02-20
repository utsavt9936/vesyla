#include <exception>
using namespace std;

#ifndef __LoopObjectDeclaration_h__
#define __LoopObjectDeclaration_h__

// #include "ForStatement.hpp"
#include "ObjectDeclaration.hpp"

namespace VIR {
class ForStatement;
// class ObjectDeclaration;
class LoopObjectDeclaration;
}

namespace VIR {
class LoopObjectDeclaration: public VIR::ObjectDeclaration {
private:
	VIR::ForStatement* _forStatement;

public:
	VIR::ForStatement * forStatement() const;

public:
	void forStatement(VIR::ForStatement * forStatement_);
};
}

#endif
