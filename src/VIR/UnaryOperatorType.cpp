#include "UnaryOperatorType.hpp"

#define OP_STR(op, opStr) case(op): str = opStr; break;
#define OP_TYPE_STR(op) case(op): str = #op; break;

string VIR::VirEnumerations::unaryOperatorStr(UnaryOperatorType opType_) {
	string str;

	switch (opType_) {
	OP_STR(uotPlus, "+")
		;
	OP_STR(uotMinus, "-")
		;
	OP_STR(uotNot, "~")
		;
	OP_STR(uotTranspose, ".'")
		;
	OP_STR(uotCTranspose, "'")
		;
	}

	return str;
}

string VIR::VirEnumerations::unaryOperatorTypeStr(UnaryOperatorType opType_) {
	string str;

	switch (opType_) {
	OP_TYPE_STR(uotPlus)
		;
	OP_TYPE_STR(uotMinus)
		;
	OP_TYPE_STR(uotNot)
		;
	OP_TYPE_STR(uotTranspose)
		;
	OP_TYPE_STR(uotCTranspose)
		;
	}

	return str.substr(3);
}
