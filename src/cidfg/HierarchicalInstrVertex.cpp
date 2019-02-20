#include "HierarchicalInstrVertex.hpp"

namespace vesyla
{
namespace cidfg
{
HierarchicalInstrVertex::HierarchicalInstrVertex()
{
	vertex_type = HIERARCHICAL_INSTR_VERTEX;
	name = "";
	rot = {};
	is_bulk = false;
}
HierarchicalInstrVertex::~HierarchicalInstrVertex()
{
}
} // namespace cidfg
} // namespace vesyla