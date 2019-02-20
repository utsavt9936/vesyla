#ifndef __VIRBase_h__
#define __VIRBase_h__

#include "KindType.hpp"
#include "util/Common.hpp"

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace MemorySpace
{
class MemoryManager;
}

namespace VIR
{
class VIRBase
{
	friend class MemorySpace::MemoryManager;

private:
	int _id;

private:
	int _lineNumber;

private:
	VIR::VirEnumerations::KindType _kind;

public:
	int id() const;

public:
	VIR::VirEnumerations::KindType kind() const;

public:
	string kindStr() const;

public:
	int lineNumber() const;

public:
	void lineNumber(const int lineNumber_);

public:
	virtual ~VIRBase() = 0;
};
} // namespace VIR

#endif
