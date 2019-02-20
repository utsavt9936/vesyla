#include "ReadAndIndexVertex.hpp"

namespace vesyla
{
namespace cidfg
{
ReadAndIndexVertex::ReadAndIndexVertex()
{
	vertex_type = READ_AND_INDEX_VERTEX;
	port = 2;
	is_sram = false;
}
ReadAndIndexVertex::~ReadAndIndexVertex()
{
}
} // namespace cidfg
} // namespace vesyla