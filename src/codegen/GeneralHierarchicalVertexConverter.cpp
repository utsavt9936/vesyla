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

#include "GeneralHierarchicalVertexConverter.hpp"
using namespace boost;
using namespace BIR;
using namespace BIR::BIREnumerations;
namespace vesyla
{
namespace codegen
{
GeneralHierarchicalVertexConverter::GeneralHierarchicalVertexConverter()
{
}
GeneralHierarchicalVertexConverter::~GeneralHierarchicalVertexConverter()
{
}
void GeneralHierarchicalVertexConverter::convert(cidfg::CidfgGraph &g_)
{
	std::set<int> gh_vertices;
	for (auto &v : g_.get_vertices())
	{
		if (v->vertex_type == cidfg::Vertex::GENERAL_HIERARCHICAL_VERTEX)
		{

			int parent_id;
			int child_index;
			g_.get_parent(v->id, parent_id, child_index);

			cidfg::HierarchicalInstrVertex ghv;
			ghv.coord = v->coord;

			cidfg::HierarchicalVertex *vv = static_cast<cidfg::HierarchicalVertex *>(v);
			for (int i = 0; i < vv->children.size(); i++)
			{
				for (int j = 0; j < vv->children[i].size(); j++)
				{
					ghv.add_child(i, vv->children[i][j]);
				}
			}

			int id_ghv = g_.add_vertex(ghv, parent_id, child_index);

			for (auto &e : g_.get_edges())
			{
				if (e->src_id == v->id)
				{
					e->src_id = id_ghv;
				}
				if (e->dest_id == v->id)
				{
					e->dest_id = id_ghv;
				}
			}
			vv->children.clear();
			gh_vertices.insert(v->id);
		}
	}

	for (auto &id : gh_vertices)
	{
		g_.del_vertex(id);
	}
}
} // namespace codegen
} // namespace vesyla