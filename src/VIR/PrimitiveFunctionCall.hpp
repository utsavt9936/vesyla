#include <exception>
using namespace std;

#ifndef __PrimitiveFunctionCall_h__
#define __PrimitiveFunctionCall_h__

#include "FunctionCall.hpp"
#include "FunctionType.hpp"

namespace VIR
{
// class FunctionCall;
class PrimitiveFunctionCall;
namespace VirEnumerations
{
// enum FunctionType;
}
} // namespace VIR

namespace VIR
{
class PrimitiveFunctionCall : public VIR::FunctionCall
{
public:
	string primitive_func_name;

private:
	VIR::VirEnumerations::FunctionType _type;

public:
	PrimitiveFunctionCall();
	VIR::VirEnumerations::FunctionType type() const;
	void type(VIR::VirEnumerations::FunctionType type_);
};
} // namespace VIR

#endif
