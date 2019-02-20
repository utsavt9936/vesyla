#include <exception>
#include <string>
using namespace std;

#ifndef __Identifier_h__
#define __Identifier_h__

#include "Name.hpp"
#include "DependencyType.hpp"
#include "VIRFwDeclarations.hpp"

namespace VIR {
// class Name;
class Identifier;
namespace VirEnumerations {
// enum DependencyType;
}
}

namespace VIR {
class Identifier: public VIR::Name {
private:
	string _name;
private:
	VIR::ObjectDeclaration * _object;
private:
	VIR::AssignmentStatement * _dependentTo;
private:
	VIR::VirEnumerations::DependencyType _dependencyType;
private:
	VIR::Statement * _indexDependency;

public:
	Identifier();

public:
	string name() const;

public:
	void name(const string & name_);

public:
	VIR::ObjectDeclaration * object() const;

public:
	void object(VIR::ObjectDeclaration * object_);

public:
	VIR::AssignmentStatement * dependentTo() const;

public:
	void dependentTo(VIR::AssignmentStatement * dependentTo_);

public:
	VIR::VirEnumerations::DependencyType dependencyType() const;

public:
	void dependencyType(VIR::VirEnumerations::DependencyType dependencyType_);

public:
	VIR::Statement * indexDependency() const;

public:
	void indexDependency(VIR::Statement * indexDependency_);
};
}

#endif
