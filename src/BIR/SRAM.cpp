#include <exception>
using namespace std;

#include "SRAM.hpp"
#include "MemElement.hpp"
#include "BIRBase.hpp"

BIR::SRAM::SRAM(int depth_, int width_)
{
	_depth = depth_;
	_width = width_;
	_hasInitialLoad = false;
	
	_memory = new BIR::MemElement * [_depth];
	for (int index = 0; index < _depth; ++index)
		_memory[index] = new BIR::MemElement(_width);
}

BIR::SRAM::~SRAM()
{
	for (int index = 0; index < _depth; ++index)
		delete _memory[index];
	delete []_memory;
}

BIR::MemElement * BIR::SRAM::memory(int index_)
{
	return _memory[index_];
}

int BIR::SRAM::depth()
{
	return _depth;
}

bool BIR::SRAM::hasInitialLoad() const
{
	return _hasInitialLoad;
}

void BIR::SRAM::hasInitialLoad(bool hasInitialLoad_)
{
	_hasInitialLoad = hasInitialLoad_;
}

