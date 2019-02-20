#ifndef __VESYLA_CIDFG_HIERARCHICAL_VERTEX_HPP__
#define __VESYLA_CIDFG_HIERARCHICAL_VERTEX_HPP__

#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
class HierarchicalVertex : public Vertex
{
public:
	vector<vector<int>> children;

public:
	HierarchicalVertex();
	virtual ~HierarchicalVertex() = 0;

public:
	void add_child(int child_index_, int child_id);
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_HIERARCHICAL_VERTEX_HPP__