// Copyright (C) 2019 Yu Yang
//
// This file is part of Vesyla.
//
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

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