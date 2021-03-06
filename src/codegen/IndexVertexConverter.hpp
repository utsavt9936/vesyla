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

#ifndef __VESYLA_CODEGEN_INDEX_VERTEX_CONVERTER_HPP__
#define __VESYLA_CODEGEN_INDEX_VERTEX_CONVERTER_HPP__

#include "cidfg/CidfgGraph.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/sequential_vertex_coloring.hpp>
#include <cidfg/VarTable.hpp>
#include "BIR/BIRIncludeAll.hpp"
#include "VManager/MemoryManager.hpp"

namespace vesyla
{
namespace codegen
{
class IndexVertexConverter
{
public:
	IndexVertexConverter();
	~IndexVertexConverter();

	void convert(cidfg::CidfgGraph &g_);
	void convert_swb(cidfg::CidfgGraph &g_);
	void convert_refi(cidfg::CidfgGraph &g_);

private:
	void assign_port(cidfg::CidfgGraph &g_);
	void convert_mrdi_wri(cidfg::CidfgGraph &g_, int src_id_, int dest_id_, std::set<int> &removed_vertices_);
	void convert_rdi_mwri(cidfg::CidfgGraph &g_, int src_id_, int dest_id_, std::set<int> &removed_vertices_);
	void convert_rdi_wri(cidfg::CidfgGraph &g_, int src_id_, int dest_id_, std::set<int> &removed_vertices_);
	void convert_rdi_other(cidfg::CidfgGraph &g_, int src_id_, int dest_id_, std::set<int> &removed_vertices_);
	void convert_other_wri(cidfg::CidfgGraph &g_, int src_id_, int dest_id_, std::set<int> &removed_vertices_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_INDEX_VERTEX_CONVERTER_HPP__