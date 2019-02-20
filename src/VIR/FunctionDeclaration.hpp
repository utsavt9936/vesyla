#include <exception>
#include <string>
using namespace std;

#ifndef __FunctionDeclaration_h__
#define __FunctionDeclaration_h__

#include "Declaration.hpp"
#include "Statement.hpp"

namespace VIR {
// class Declaration;
class FunctionDeclaration;
}

namespace VIR {
class FunctionDeclaration: public VIR::Declaration {
private:
	vector<Statement*> _body;
private:
	string _name;
private:
	vector<Statement*> _totalAssignmentStatements;

public:
	vector<Statement*> & body();

public:
	string name() const;

public:
	void name(const string & name_);

public:
	vector<Statement*> & totalAssignmentStatements();
};
}

#endif
