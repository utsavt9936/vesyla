#include "HierarchicalVertex.hpp"

namespace vesyla
{
namespace cidfg
{
HierarchicalVertex::HierarchicalVertex()
{
}
HierarchicalVertex::~HierarchicalVertex()
{
}
void HierarchicalVertex::add_child(int child_index_, int child_id)
{
	if (child_index_ >= children.size())
	{
		children.resize(child_index_ + 1, {});
	}
	children[child_index_].push_back(child_id);
}
} // namespace cidfg
} // namespace vesyla