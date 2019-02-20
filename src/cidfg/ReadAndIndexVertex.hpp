#ifndef __VESYLA_CIDFG_READ_AND_INDEX_VERTEX_HPP__
#define __VESYLA_CIDFG_READ_AND_INDEX_VERTEX_HPP__

#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
class ReadAndIndexVertex : public Vertex
{
public:
	int port;
	bool is_sram;
	VIR::Coordinate sram_coord;

public:
	ReadAndIndexVertex();
	~ReadAndIndexVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_READ_AND_INDEX_VERTEX_HPP__