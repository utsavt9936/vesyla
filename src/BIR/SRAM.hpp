#include <exception>
using namespace std;

#ifndef __SRAM_h__
#define __SRAM_h__

// #include "MemElement.hpp"
#include "BIRBase.hpp"

namespace BIR
{
class MemElement;
// class BIRBase;
class SRAM;
} // namespace BIR

namespace BIR
{
class SRAM : public BIR::BIRBase
{
private:
	int _depth;

private:
	int _width;

private:
	BIR::MemElement **_memory;

private:
	bool _hasInitialLoad;

public:
	SRAM(int depth_, int width_);

public:
	~SRAM();

public:
	BIR::MemElement *memory(int index_);

public:
	int depth();
	int width() { return _width; }

public:
	bool hasInitialLoad() const;

public:
	void hasInitialLoad(bool hasInitialLoad_);
};
} // namespace BIR

#endif
