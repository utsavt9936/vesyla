#ifndef __VESYLA_FEOPT_RWI_MERGE_ENGINE_HPP__
#define __VESYLA_FEOPT_RWI_MERGE_ENGINE_HPP__

#include "Engine.hpp"

namespace vesyla
{
namespace feopt
{
class RwiMergeEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);

private:
	void merge_rw_index(cidfg::CidfgGraph &g_, set<int> &children_id_, int vertex_id_, int parent_vertex_id_, int child_index_, set<int> &removed_vertices_);
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_RWI_MERGE_ENGINE_HPP__