#include <exception>
using namespace std;

#include "RegFile.hpp"

#include "AGU.hpp"
#include "Register.hpp"
#include "BIRBase.hpp"

BIR::RegFile::RegFile(int regDepth_)
{
	_regDepth = regDepth_;
	_hasInitialLoad = false;
	
	_registers = new BIR::Register * [_regDepth];
	for (int index = 0; index < _regDepth; ++index)
		_registers[index] = new BIR::Register();
	
	for (int i = 0; i < 4; ++i)
		_agus[i] = new BIR::AGU();
}

BIR::RegFile::~RegFile()
{
	for (int index = 0; index < _regDepth; ++index)
		delete _registers[index];
	delete []_registers;
	
	for (int i = 0; i < 4; ++i)
		delete _agus[i];
}

BIR::AGU * BIR::RegFile::agu(int index_)
{
	return _agus[index_];
}

int BIR::RegFile::regDepth() const
{
	return _regDepth;
}

bool BIR::RegFile::hasInitialLoad() const
{
	return _hasInitialLoad;
}

void BIR::RegFile::hasInitialLoad(bool hasInitialLoad_)
{
	_hasInitialLoad = hasInitialLoad_;
}

BIR::Register* BIR::RegFile::registers(int index_) const
{
	return _registers[index_];
}

