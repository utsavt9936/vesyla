#include "WritingVertex.hpp"

namespace vesyla
{
namespace cidfg
{
WritingVertex::WritingVertex()
{
	vertex_type = WRITING_VERTEX;
	is_sram = false;
}
WritingVertex::~WritingVertex()
{
}
} // namespace cidfg
} // namespace vesyla