#include <exception>
using namespace std;

#include "BIRBase.hpp"
#include "BIRKindType.hpp"

int BIR::BIRBase::id() const
{
	return _id;
}

void BIR::BIRBase::id(int id_)
{
	_id = id_;
}

BIR::BIREnumerations::BIRKindType BIR::BIRBase::kind() const
{
	return _kind;
}

string BIR::BIRBase::kindStr() const {
	string str="unknown type";
	
	switch(_kind){
	case BIR::BIREnumerations::bktAGU: str = "AGU"; break;
	case BIR::BIREnumerations::bktBranchInstruction: str = "BranchInstruction"; break;
	case BIR::BIREnumerations::bktContileCell: str = "ContileCell"; break;
	case BIR::BIREnumerations::bktDiMArch: str = "DiMArch"; break;
	case BIR::BIREnumerations::bktDiMArchCell: str = "DiMArchCell"; break;
	case BIR::BIREnumerations::bktDPU: str = "DPU"; break;
	case BIR::BIREnumerations::bktDRRACell: str = "DRRACell"; break;
	case BIR::BIREnumerations::bktDRRACluster: str = "DRRACluster"; break;
	case BIR::BIREnumerations::bktDPUInstruction: str = "DPUInstruction"; break;
	case BIR::BIREnumerations::bktLoopHeaderInstruction: str = "LoopHeaderInstruction"; break;
	case BIR::BIREnumerations::bktLoopTailInstruction: str = "LoopTailInstruction"; break;
	case BIR::BIREnumerations::bktJumpInstruction: str = "JumpInstruction"; break;
	case BIR::BIREnumerations::bktMemoryElement: str = "MemoryElement"; break;
	case BIR::BIREnumerations::bktRACCU: str = "RACCU"; break;
	case BIR::BIREnumerations::bktRACCUInstruction: str = "RACCUInstruction"; break;
	case BIR::BIREnumerations::bktRefiInstruction: str = "RefiInstruction"; break;
	case BIR::BIREnumerations::bktRefi1Instruction: str = "Refi1Instruction"; break;
	case BIR::BIREnumerations::bktRefi2Instruction: str = "Refi2Instruction"; break;
	case BIR::BIREnumerations::bktRefi3Instruction: str = "Refi3Instruction"; break;
	case BIR::BIREnumerations::bktRegister: str = "Register"; break;
	case BIR::BIREnumerations::bktRegFile: str = "RegFile"; break;
	case BIR::BIREnumerations::bktRFILEInstruction: str = "RFILEInstruction"; break;
	case BIR::BIREnumerations::bktRouteInstruction: str = "RouteInstruction"; break;
	case BIR::BIREnumerations::bktSequencer: str = "Sequencer"; break;
	case BIR::BIREnumerations::bktSRAM: str = "SRAM"; break;
	case BIR::BIREnumerations::bktSRAMInstruction: str = "SRAMInstruction"; break;
	case BIR::BIREnumerations::bktSWBInstruction: str = "SWBInstruction"; break;
	case BIR::BIREnumerations::bktSwitchBox: str = "SwitchBox"; break;
	case BIR::BIREnumerations::bktWaitInstruction: str = "WaitInstruction"; break;
	default: break;
	}
	
	return str;
}

BIR::BIRBase::~BIRBase()
{
//	throw "Not yet implemented";
}

