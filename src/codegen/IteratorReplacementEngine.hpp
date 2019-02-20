#ifndef __VESYLA_CODEGEN_ITERATOR_REPLACEMENT_ENGINE_HPP__
#define __VESYLA_CODEGEN_ITERATOR_REPLACEMENT_ENGINE_HPP__

#include "Engine.hpp"

namespace vesyla
{
namespace codegen
{
/**
 * This class transform iterator to a RACCU variable if it works as operand of
 * multiplication operation.
 * The transformation is needed because RACCU don't have multiplication unit and
 * even shifting unit can't work with iterator.
 */
class IteratorReplacementEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_ITERATOR_REPLACEMENT_ENGINE_HPP__