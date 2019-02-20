#ifndef __FunctionType_h__
#define __FunctionType_h__

namespace VIR {
namespace VirEnumerations {
// enum FunctionType;
}
}

namespace VIR {
namespace VirEnumerations {
enum FunctionType {
	ftUndefine,
	ftAbsSubAcc,
	ftFixedPoint,
	ftMac,
	ftMax,
	ftMin,
	ftOnes,
	ftPreservingMac,
	ftShiftLeft,
	ftShiftRight,
	ftSymmetricMac,
	ftZeros,
	ftSubAcc,
	ftSigmoid,
	ftTanh,
	ftButterfly
};
}
}

#endif
