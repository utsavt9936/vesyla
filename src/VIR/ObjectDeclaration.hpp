#include <exception>
#include <string>
using namespace std;

#ifndef __ObjectDeclaration_h__
#define __ObjectDeclaration_h__

#include "Declaration.hpp"
#include "ObjectType.hpp"
#include "NumericLiteral.hpp"
#include "AssignmentPragma.hpp"

namespace VIR {
// class Declaration;
class ObjectDeclaration;
namespace VirEnumerations {
// enum ObjectType;
}
}

namespace VIR {
class ObjectDeclaration: public VIR::Declaration {
private:
	string _name;
private:
	VIR::NumericLiteral * _value;
private:
	VIR::AssignmentPragma * _pragma;
private:
	VIR::VirEnumerations::ObjectType _objectType;
private:
	bool _isFixedPointVariable;

public:
	ObjectDeclaration();

public:
	string name() const;

public:
	void name(const string & name_);

public:
	VIR::NumericLiteral * value() const;

public:
	void value(NumericLiteral * value_);

public:
	VIR::AssignmentPragma * pragma() const;

public:
	void pragma(VIR::AssignmentPragma * pragma_);

public:
	VIR::VirEnumerations::ObjectType objectType() const;

public:
	void objectType(VIR::VirEnumerations::ObjectType objectType_);

public:
	bool isLoopIndex() const;

public:
	bool isFixedPointVariable() const;

public:
	void isFixedPointVariable(bool isFixedPointVariable_);
};
}

#endif
