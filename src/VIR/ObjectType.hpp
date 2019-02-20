#ifndef __ObjectType_h__
#define __ObjectType_h__

namespace VIR {
namespace VirEnumerations {
// enum ObjectType;
}
}

namespace VIR {
namespace VirEnumerations {
enum ObjectType {
	otNone,
	otAddressVariable,
	otAffineAddressFunction,
	otConstant,
	otConstantLoopIndex,
	otDPUChain,
	otIndirectAddressVariable,
	otMemory,
	otNonAffineAddressFunction,
	otNonConstantLoopIndex,
	otRaccuVariable,
	otRegisterFile,
	otTempVariable
};
}
}

#endif
