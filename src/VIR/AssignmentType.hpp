#ifndef __AssignmentType_h__
#define __AssignmentType_h__

namespace VIR {
namespace VirEnumerations {
// enum AssignmentType;
}
}

namespace VIR {
namespace VirEnumerations {
enum AssignmentType {
	atAddressCalculation,
	atAddressVariable,
	atArithmetic,
	atConstant,
	atDeclarative,
	atDPUChainConnection,
	atDPUChainDeclaration,
	atIndirectAddressDeclaration,
	atMemoryTransfer,
	atRaccuVariable,
	atRegisterTransfer,
	atTempAssignment,
	atTempVariable
};
}
}

#endif
