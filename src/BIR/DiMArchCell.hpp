#include <exception>
using namespace std;

#ifndef __DiMArchCell_h__
#define __DiMArchCell_h__

#include "BIRBase.hpp"
#include "SRAM.hpp"

namespace BIR
{
	// class BIRBase;
	class DiMArchCell;
}

namespace BIR
{
	class DiMArchCell: public BIR::BIRBase
	{
		private: BIR::SRAM * _sram;

		public: DiMArchCell(int sramDepth_, int sramWidth_);

		public: ~DiMArchCell();

		public: BIR::SRAM * sram();
	};
}

#endif
