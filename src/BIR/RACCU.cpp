#include <exception>
using namespace std;

#include "RACCU.hpp"
#include "BIRBase.hpp"

BIR::RACCU::RACCU(int raccuDepth_, int raccuMaxLoopNo_)
{
	_raccuDepth = raccuDepth_;
	_raccuMaxLoopNo = raccuMaxLoopNo_;
	_currFreeAddress = -1;
	_currFreeLoopId = -1;
}

int BIR::RACCU::getFreeAddress()
{
	++_currFreeAddress;
	
	return _currFreeAddress <= _raccuDepth ? _currFreeAddress : -1;
}

int BIR::RACCU::getFreeLoopId()
{
	++_currFreeLoopId;
	
	return _currFreeLoopId <= _raccuMaxLoopNo ? _currFreeLoopId : -1;
}

