#include <exception>
using namespace std;

#include "DiMArchCell.hpp"
#include "SRAM.hpp"
#include "BIRBase.hpp"

BIR::DiMArchCell::DiMArchCell(int sramDepth_, int sramWidth_)
{
	_sram = new BIR::SRAM(sramDepth_, sramWidth_);
}

BIR::DiMArchCell::~DiMArchCell()
{
	delete _sram;
}

BIR::SRAM * BIR::DiMArchCell::sram()
{
	return _sram;
}

