#include "LoopVertex.hpp"

namespace vesyla
{
namespace cidfg
{
LoopVertex::LoopVertex()
{
	vertex_type = LOOP_VERTEX;
	loop_id = -1;
}
LoopVertex::~LoopVertex()
{
}
} // namespace cidfg
} // namespace vesyla