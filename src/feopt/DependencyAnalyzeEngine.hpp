#ifndef __VESYLA_FEOPT_DEPENDENCY_ANALYZE_ENGINE_HPP__
#define __VESYLA_FEOPT_DEPENDENCY_ANALYZE_ENGINE_HPP__

#include "Engine.hpp"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>

namespace vesyla
{
namespace feopt
{
class DependencyAnalyzeEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);

private:
	vector<int> get_addr_info(cidfg::CidfgGraph &g_, int vid_);
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_DEPENDENCY_ANALYZE_ENGINE_HPP__