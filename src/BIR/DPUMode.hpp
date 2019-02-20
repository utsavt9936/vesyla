
#ifndef __DPUMode_h__
#define __DPUMode_h__

namespace BIR
{
	namespace BIREnumerations
	{
		// enum DPUMode;
	}
}

namespace BIR
{
	namespace BIREnumerations
	{
		enum DPUMode
		{
			dmUnspecified, dmAbsSubAcc, dmAdd, dmAddWithConstant, dmComparison, dmComparisonWithConstant, dmFFT1, dmFFT2, dmLoadConstant, dmMac, dmMax, dmMin, dmMult, dmPreservingMac, dmSub, dmSubAcc, dmSymMac, dmSymFirWithIMac, dmSymFirWithEMac, dmASymFirWithIMac, dmASymFirWithEMac, dmTwoAdders, dmTwoSubtractors, dmFourInputAdder, dmDiffOfSum, dmSumOfDiff, dmLFSR, dmShiftLeft, dmShiftRight, dmAndOr, dmAndOrWithStatusBit, dmReset,
			dmSigmoid, dmTanh
		};
	}
}

#endif
