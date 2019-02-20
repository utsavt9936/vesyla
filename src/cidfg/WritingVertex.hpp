#ifndef __VESYLA_CIDFG_WRITING_VERTEX_HPP__
#define __VESYLA_CIDFG_WRITING_VERTEX_HPP__

#include "FunctionVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class WritingVertex : public FunctionVertex
{
public:
	bool is_sram;

public:
	WritingVertex();
	~WritingVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_WRITING_VERTEX_HPP__