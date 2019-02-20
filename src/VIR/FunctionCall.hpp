#include <exception>
using namespace std;

#ifndef __FunctionCall_h__
#define __FunctionCall_h__

#include "Expression.hpp"
#include "Identifier.hpp"

namespace VIR {
// class Expression;
class FunctionCall;
}

namespace VIR {
class FunctionCall: public VIR::Expression {
public:
	VIR::Identifier * _name;
	vector<Expression*> _parameters;
	vector<Expression*> _parametersSplit;

public:
	VIR::Identifier* name(){
		return _name;
	}
	void name(Identifier* name_){
		_name=name_;
	}
	vector<Expression*> & parameters(){
		return _parameters;
	}
	vector<Expression*> & parametersSplit(){
		return _parametersSplit;
	}
};
}

#endif
