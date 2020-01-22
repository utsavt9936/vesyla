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

#ifndef __VESYLA_CODEGEN_RACCU_REG_ALLOC_ENGINE_HPP__
#define __VESYLA_CODEGEN_RACCU_REG_ALLOC_ENGINE_HPP__

#include "Engine.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/sequential_vertex_coloring.hpp>

namespace vesyla
{
namespace codegen
{
class RaccuRegAllocEngine : Engine
{
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, int, string> Graph;

public:
	RaccuRegAllocEngine() = default;
	~RaccuRegAllocEngine() = default;
	void transform(cidfg::CidfgGraph &g_);

private:
	void create_graph(cidfg::CidfgGraph &g_, Graph &g0_, VIR::Coordinate coord_, std::unordered_map<int, Graph::vertex_descriptor> &map_g2g0, std::unordered_map<Graph::vertex_descriptor, int> &map_g02g);
	int pre_assign(Graph &g0_);
	void pre_group(Graph &g0_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_RACCU_REG_ALLOC_ENGINE_HPP__