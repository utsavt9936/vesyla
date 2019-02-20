#ifndef __DependencyType_h__
#define __DependencyType_h__

namespace VIR {
namespace VirEnumerations {
// enum DependencyType;
}
}

namespace VIR {
namespace VirEnumerations {
enum DependencyType {
	dtNone, dtReadAfterWrite, dtWriteAfterRead, dtWriteAfterWrite
};
}
}

#endif
