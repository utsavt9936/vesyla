#include <exception>
using namespace std;

#ifndef __SwitchBox_h__
#define __SwitchBox_h__

#include "BIRBase.hpp"

namespace BIR
{
	// class BIRBase;
	class SwitchBox;
}

namespace BIR
{
	class SwitchBox: public BIR::BIRBase
	{
		private: int * _inputOutputConnections;
		private: int _inputNum;
		private: int _outputNum;

		public: SwitchBox(int inputNum_ = 14, int outputNum_ = 12);

		public: ~SwitchBox();

		public: void setAConnection(int inputIndex_, int outputIndex_, bool enable_ = true);

		public: int getAConnection(int outputIndex_) const;
	};
}

#endif
