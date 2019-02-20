
#ifndef __BIRKindType_h__
#define __BIRKindType_h__

namespace BIR
{
	namespace BIREnumerations
	{
		// enum BIRKindType;
	}
}

namespace BIR
{
	namespace BIREnumerations
	{
		enum BIRKindType
		{
			bktAGU, bktBranchInstruction, bktContileCell, bktDiMArch, bktDiMArchCell, bktDPU, bktDRRACell, bktDRRACluster, bktDPUInstruction, bktLoopHeaderInstruction, bktLoopTailInstruction, bktJumpInstruction, bktMemoryElement, bktRACCU, bktRACCUInstruction, bktRefiInstruction, bktRefi1Instruction, bktRefi2Instruction, bktRefi3Instruction, bktRegister, bktRegFile, bktRFILEInstruction, bktRouteInstruction, bktSequencer, bktSRAM, bktSRAMInstruction, bktSWBInstruction, bktSwitchBox, bktWaitInstruction
		};
	}
}

#endif
