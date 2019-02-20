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