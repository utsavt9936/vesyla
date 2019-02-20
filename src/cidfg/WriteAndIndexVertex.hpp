#ifndef __VESYLA_CIDFG_WRITE_AND_INDEX_VERTEX_HPP__
#define __VESYLA_CIDFG_WRITE_AND_INDEX_VERTEX_HPP__

#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
class WriteAndIndexVertex : public Vertex
{
public:
	int port;
	bool is_sram;
	VIR::Coordinate sram_coord;

public:
	WriteAndIndexVertex();
	~WriteAndIndexVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_WRITE_AND_INDEX_VERTEX_HPP__