#ifndef __VESYLA_CIDFG_LOOP_VERTEX_HPP__
#define __VESYLA_CIDFG_LOOP_VERTEX_HPP__

#include "HierarchicalVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class LoopVertex : public HierarchicalVertex
{
public:
	string iterator_name;
	int loop_id;

public:
	LoopVertex();
	~LoopVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_LOOP_VERTEX_HPP__