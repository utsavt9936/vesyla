#ifndef __VESYLA_CIDFG_SINK_VERTEX_HPP__
#define __VESYLA_CIDFG_SINK_VERTEX_HPP__

#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
class SinkVertex : public Vertex
{
public:
	string var_name;
	VIR::Coordinate sram_coord;

public:
	SinkVertex();
	virtual ~SinkVertex() = 0;
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_SINK_VERTEX_HPP__