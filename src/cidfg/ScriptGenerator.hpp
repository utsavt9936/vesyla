#ifndef __VESYLA_CIDFG_SCRIPT_GENERATOR_HPP__
#define __VESYLA_CIDFG_SCRIPT_GENERATOR_HPP__

#include "util/Common.hpp"

namespace vesyla
{
namespace cidfg
{
class ScriptGenerator
{
public:
	ScriptGenerator();
	~ScriptGenerator();
	string generate();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_SCRIPT_GENERATOR_HPP__