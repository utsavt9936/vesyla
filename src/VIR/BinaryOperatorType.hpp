#ifndef __BinaryOperatorType_h__
#define __BinaryOperatorType_h__

#include <string>
using std::string;

namespace VIR {
namespace VirEnumerations {
// enum BinaryOperatorType;
}
}

namespace VIR {
namespace VirEnumerations {
enum BinaryOperatorType {
	botAdd,
	botSub,
	botMPower,
	botEPower,
	botMMul,
	botEMul,
	botMDiv,
	botEDiv,
	botMLeftDiv,
	botELeftDiv,
	botEqual,
	botUnEqual,
	botGreaterThan,
	botGreaterOrEqual,
	botLessThan,
	botLessOrEqual,
	botAnd,
	botOr
};

string binaryOperatorStr(BinaryOperatorType opType_);
string binaryOperatorTypeStr(BinaryOperatorType opType_);
}
}

#endif
