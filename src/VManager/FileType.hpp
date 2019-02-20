
#ifndef _FileType_H_
#define _FileType_H_

typedef enum
{
	ftReport = 0, ftDumpDs, ftDumpElabDs, ftElaborator, ftInstructions, ftMakeFirstRun, ftMakeGraph, ftMakeRerun, 
	ftManas, ftMatlab, ftOptimizedSchedules, ftParser, ftProfiler, ftRunCmd, ftRunGui, ftSchedules,
	ftSyncInstructions, ftTimingModel, ftVhdlTestbench, ftVhdlPackage, ftVirDot1, ftVirDot2, ftVirDot3, ftVirDot4,
	ftVirElabDot1, ftVirElabDot2, ftVirElabDot3, ftVirElabDot4, ftWave, 
	cFileNumber
} FileType;

#endif // _FileType_H_