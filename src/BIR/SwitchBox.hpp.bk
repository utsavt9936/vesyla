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
