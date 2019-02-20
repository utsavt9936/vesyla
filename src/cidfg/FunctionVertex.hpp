#ifndef __VESYLA_CIDFG_FUNCTION_VERTEX_HPP__
#define __VESYLA_CIDFG_FUNCTION_VERTEX_HPP__

#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
class FunctionVertex : public Vertex
{
public:
	FunctionVertex();
	virtual ~FunctionVertex() = 0;
};

} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_FUNCTION_VERTEX_HPP__