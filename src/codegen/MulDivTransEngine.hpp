#ifndef __VESYLA_CODEGEN_MUL_DIV_TRANS_ENGINE_HPP__
#define __VESYLA_CODEGEN_MUL_DIV_TRANS_ENGINE_HPP__

#include "Engine.hpp"

namespace vesyla
{
namespace codegen
{
class MulDivTransEngine : public Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_MUL_DIV_TRANS_ENGINE_HPP__