#include "VarVertex.hpp"

namespace vesyla
{
namespace cidfg
{
VarVertex::VarVertex()
{
	vertex_type = VAR_VERTEX;
	is_iterator = false;
}
VarVertex::~VarVertex()
{
}
} // namespace cidfg
} // namespace vesyla