#include "CleanConverter.hpp"

namespace vesyla
{
namespace codegen
{
CleanConverter::CleanConverter()
{
}
CleanConverter::~CleanConverter()
{
}
void CleanConverter::convert(cidfg::CidfgGraph &g_)
{
	std::set<int> remove_vertices;

	for (auto &v : g_.get_vertices())
	{
		if (v->vertex_type == cidfg::Vertex::ROOT_VERTEX)
		{
			continue;
		}
		if (v->vertex_type == cidfg::Vertex::MERGE_VERTEX)
		{
			int parent_id = -1;
			int child_index = -1;
			g_.get_parent(v->id, parent_id, child_index);
			cidfg::HierarchicalInstrVertex hiv;
			int id_hiv = g_.add_vertex(hiv, parent_id, child_index);
			for (auto &e : g_.get_edges())
			{
				if (e->src_id == v->id)
				{
					e->src_id = id_hiv;
				}
				if (e->dest_id == v->id)
				{
					e->dest_id = id_hiv;
				}
			}
			remove_vertices.insert(v->id);
			continue;
		}
		if (!(v->is_instr()))
		{
			remove_vertices.insert(v->id);
		}
	}

	for (auto &id : remove_vertices)
	{
		g_.del_vertex(id);
	}

	// Convert all links that are not dependency link to dependency link with distance [1,+INF)
	// for (auto &e : g_.get_edges())
	// {
	// 	if (e->edge_type != cidfg::Edge::DEPENDENCY)
	// 	{
	// 		e->edge_type = cidfg::Edge::DEPENDENCY;
	// 		e->d_lo = 1;
	// 		e->d_hi = INT_MAX;
	// 	}
	// }
}
} // namespace codegen
} // namespace vesyla