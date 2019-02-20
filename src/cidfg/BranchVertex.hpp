#ifndef __VESYLA_CIDFG_BRANCH_VERTEX_HPP__
#define __VESYLA_CIDFG_BRANCH_VERTEX_HPP__

#include "HierarchicalVertex.hpp"
namespace vesyla
{
namespace cidfg
{
class BranchVertex : public HierarchicalVertex
{
public:
	BranchVertex();
	~BranchVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_BRANCH_VERTEX_HPP__