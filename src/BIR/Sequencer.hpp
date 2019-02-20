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
#include <map>
using namespace std;

#ifndef __Sequencer_h__
#define __Sequencer_h__

#include "InstructionList.hpp"
#include "BIRBase.hpp"
#include "RACCU.hpp"

namespace BIR
{
	class InstructionList;
	// class BIRBase;
	class Sequencer;
}

namespace BIR
{
	class Sequencer: public BIR::BIRBase
	{
		public: int sequencerMaxClk;
		public: map<int, BIR::InstructionList> instructionsSequence;
		public: map<int, BIR::InstructionList> optimizedInstructionsSequence;
		private: BIR::RACCU * _raccu;

		public: Sequencer(int raccuDepth_, int raccuMaxLoopNo_);

		public: Sequencer();

		public: ~Sequencer();

		public: BIR::RACCU * raccu() const;
	};
}

#endif
