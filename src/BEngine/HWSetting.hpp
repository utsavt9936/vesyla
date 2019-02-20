
#ifndef _HWSetting_H_
#define _HWSetting_H_

struct FabricSetting
{
	int dimarchRowNumber;
	int dimarchColNumber;
	int drraRowNumber;
	int drraColNumber;
	int raccuMaxLoopNo;
	int raccuRegFileDepth;
	int regFileDepth;
	int seqRegFileDepth;
	int sramWidth;
	int sramDepth;
};

struct InstructionSetting
{
	int width;
};

struct Refi1Setting
{
	int startingAddress;
	int initDelay;
	int maxInitDelay;
};

struct Refi2Setting
{
	int stepValue;
	int middleDelay;
	int repetitionNumber;
	int repetitionStepValue;
	int maxMiddleDelay;
	int maxRepetitionNumber;
	int maxRepetitionStepValue;
};

struct Refi3Setting
{
	int repetitionDelay;
	int middleDelayExt;
	int repetitionNumberExt;
	int repetitionStepValueExt;
};

struct DpuSetting
{
	int constantWidth;
};

struct HWSetting
{
	FabricSetting fabricSetting;
	InstructionSetting instSetting;
	Refi1Setting refi1;
	Refi2Setting refi2;
	Refi3Setting refi3;
	DpuSetting dpu;
};

#endif // _HWSetting_H_