#ifndef __VESYLA_CIDFG_BINDER_HPP__
#define __VESYLA_CIDFG_BINDER_HPP__

#include "CidfgGraph.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>

namespace vesyla
{
namespace cidfg
{
class Binder
{
public:
	Binder();
	~Binder();

public:
	void fill_coord(CidfgGraph &g_);
	void split_vertex(CidfgGraph &g_);
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_BINDER_HPP__