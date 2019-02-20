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
