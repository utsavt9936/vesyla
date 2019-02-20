#include <exception>
#include <string>
using namespace std;

#include "DebugStatement.hpp"
#include "Statement.hpp"

string VIR::DebugStatement::debugStr() const {
	return _debugStr;
}

void VIR::DebugStatement::debugStr(const string& debugStr_) {
	_debugStr = debugStr_;
}

