#include "WriteAndIndexVertex.hpp"

namespace vesyla
{
namespace cidfg
{
WriteAndIndexVertex::WriteAndIndexVertex()
{
	vertex_type = WRITE_AND_INDEX_VERTEX;
	port = 0;
	is_sram = false;
}
WriteAndIndexVertex::~WriteAndIndexVertex()
{
}
} // namespace cidfg
} // namespace vesyla