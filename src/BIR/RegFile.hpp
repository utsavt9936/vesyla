// Copyright (C) 2019 Yu Yang
// 
// This file is part of Vesyla.
// 
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

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
