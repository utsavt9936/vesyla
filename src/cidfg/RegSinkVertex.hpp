#ifndef __VESYLA_CIDFG_REG_SINK_VERTEX_HPP__
#define __VESYLA_CIDFG_REG_SINK_VERTEX_HPP__

#include "SinkVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class RegSinkVertex : public SinkVertex
{
public:
	RegSinkVertex();
	~RegSinkVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif