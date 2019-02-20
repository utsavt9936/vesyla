#ifndef __VESYLA_CIDFG_VAR_SINK_VERTEX_HPP__
#define __VESYLA_CIDFG_VAR_SINK_VERTEX_HPP__

#include "SinkVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class VarSinkVertex : public SinkVertex
{
public:
	VarSinkVertex();
	~VarSinkVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif