#ifndef __UnaryOperatorType_h__
#define __UnaryOperatorType_h__

#include <string>
using std::string;

namespace VIR {
namespace VirEnumerations {
// enum UnaryOperatorType;
}
}

namespace VIR {
namespace VirEnumerations {
enum UnaryOperatorType {
	uotPlus, uotMinus, uotNot, uotTranspose, uotCTranspose
};

string unaryOperatorStr(UnaryOperatorType opType_);
string unaryOperatorTypeStr(UnaryOperatorType opType_);
}
}

#endif
