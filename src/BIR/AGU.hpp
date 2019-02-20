#include <exception>
using namespace std;

#ifndef __AGU_h__
#define __AGU_h__

#include "BIRBase.hpp"

namespace BIR{
	// class BIRBase;
	class AGU;
}

namespace BIR
{
	class AGU: public BIR::BIRBase
	{
		private: int _clkCounter;

		public: AGU();

		public: ~AGU();

		public: int clkCounter() const;

		public: void clkCounter(int clkCounter_);
	};
}

#endif
