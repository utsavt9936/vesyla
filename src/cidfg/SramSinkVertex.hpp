#ifndef __VESYLA_CIDFG_SRAM_SINK_VERTEX_HPP__
#define __VESYLA_CIDFG_SRAM_SINK_VERTEX_HPP__

#include "SinkVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class SramSinkVertex : public SinkVertex
{
public:
	VIR::Coordinate sram_coord;

public:
	SramSinkVertex();
	~SramSinkVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif