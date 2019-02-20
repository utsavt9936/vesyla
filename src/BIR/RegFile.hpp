#include <exception>
using namespace std;

#ifndef __RegFile_h__
#define __RegFile_h__

#include "Register.hpp"
#include "BIRBase.hpp"
#include "AGU.hpp"

namespace BIR
{
	class Register;
	// class BIRBase;
	class RegFile;
}

namespace BIR
{
	class RegFile: public BIR::BIRBase
	{
		private: int _regDepth;
		private: BIR::AGU * _agus[4];
		private: bool _hasInitialLoad;
		public: BIR::Register** _registers;

		public: RegFile(int regDepth_);

		public: ~RegFile();

		public: BIR::AGU * agu(int index_);

		public: int regDepth() const;

		public: bool hasInitialLoad() const;

		public: void hasInitialLoad(bool hasInitialLoad_);

		public: BIR::Register* registers(int index_) const;
	};
}

#endif
