

#ifndef __DebugStatement_h__
#define __DebugStatement_h__

#include <exception>
#include <string>
using namespace std;
#include "Statement.hpp"

namespace VIR
{
// class Statement;
class DebugStatement;
} // namespace VIR

namespace VIR
{
class DebugStatement : public VIR::Statement
{
private:
	string _debugStr;

public:
	string debugStr() const;

public:
	void debugStr(const string &debugStr_);
};
} // namespace VIR

#endif
