#include <exception>
using namespace std;

#include "AGU.hpp"
#include "BIRBase.hpp"

BIR::AGU::AGU()
{
	_clkCounter = 0;
}

BIR::AGU::~AGU()
{
//	throw "Not yet implemented";
}

int BIR::AGU::clkCounter() const
{
	return _clkCounter;
}

void BIR::AGU::clkCounter(int clkCounter_)
{
	_clkCounter = clkCounter_;
}

