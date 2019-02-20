#ifndef __VESYLA_VIR_FUNCTION_CALL_STATEMENT_HPP__
#define __VESYLA_VIR_FUNCTION_CALL_STATEMENT_HPP__

#include "Statement.hpp"

namespace VIR
{
class FunctionCallStatement : public VIR::Statement
{
public:
	VIR::FunctionCall *function_call;
	VIR::AssignmentPragma *pragma;
};
} // namespace VIR

#endif // __VESYLA_VIR_FUNCTION_CALL_STATEMENT_HPP__
