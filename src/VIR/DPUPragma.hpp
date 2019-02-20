#include <exception>
using namespace std;

#ifndef __DPUPragma_h__
#define __DPUPragma_h__

#include "../BIR/DPUMode.hpp"
#include "ReferencePragma.hpp"

namespace BIR
{
namespace BIREnumerations
{
// enum DPUMode;
}
} // namespace BIR
namespace VIR
{
// class ReferencePragma;
class DPUPragma;
} // namespace VIR

namespace VIR
{
class DPUPragma : public VIR::ReferencePragma
{
public:
	string dpuMode;

public:
	int outPort;

public:
	bool saturation;

public:
	DPUPragma();
};
} // namespace VIR

#endif
