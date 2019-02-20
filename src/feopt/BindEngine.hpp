#ifndef __VESYLA_FEOPT_BIND_ENGINE_HPP__
#define __VESYLA_FEOPT_BIND_ENGINE_HPP__

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
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, cidfg::Vertex *, cidfg::Edge *> AGraph;
class BindEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);
	std::vector<cidfg::Edge> _dependency_edges;

private:
	void fill_coord(cidfg::CidfgGraph &g_);
	void split_vertex(cidfg::CidfgGraph &g_);
	void clean(cidfg::CidfgGraph &g_);
	void record_needed_vertices(boost::graph_traits<AGraph>::vertex_descriptor v_, AGraph &g0_, set<int> &needed_vertices_);
	void find_and_remove_dependency_edges(cidfg::CidfgGraph &g_);
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_BIND_ENGINE_HPP__