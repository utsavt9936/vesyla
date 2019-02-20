#include <exception>
using namespace std;

#ifndef __RACCU_h__
#define __RACCU_h__

#include "BIRBase.hpp"

namespace BIR
{
	// class BIRBase;
	class RACCU;
}

namespace BIR
{
	class RACCU: public BIR::BIRBase
	{
		private: int _currFreeAddress;
		private: int _currFreeLoopId;
		private: int _raccuDepth;
		private: int _raccuMaxLoopNo;

		public: RACCU(int raccuDepth_, int raccuMaxLoopNo_);

		public: int getFreeAddress();

		public: int getFreeLoopId();
	};
}

#endif
