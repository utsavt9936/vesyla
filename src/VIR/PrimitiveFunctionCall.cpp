#include <exception>
using namespace std;

#include "PrimitiveFunctionCall.hpp"
#include "FunctionCall.hpp"
#include "FunctionType.hpp"

VIR::PrimitiveFunctionCall::PrimitiveFunctionCall()
{
	primitive_func_name = "";
}

VIR::VirEnumerations::FunctionType VIR::PrimitiveFunctionCall::type() const
{

	return _type;
}

void VIR::PrimitiveFunctionCall::type(
		VIR::VirEnumerations::FunctionType type_)
{
	_type = type_;
}
