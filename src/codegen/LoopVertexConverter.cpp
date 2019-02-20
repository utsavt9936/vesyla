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

#include "LoopVertexConverter.hpp"
using namespace boost;
using namespace BIR;
using namespace BIR::BIREnumerations;
namespace vesyla
{
namespace codegen
{
LoopVertexConverter::LoopVertexConverter()
{
}
LoopVertexConverter::~LoopVertexConverter()
{
}
void LoopVertexConverter::convert(cidfg::CidfgGraph &g_)
{
	std::set<int> loop_vertices;
	vector<int> loop_hierarchical_vertices;
	vector<int> loop_hierarchical_vertices_header;
	vector<int> loop_hierarchical_vertices_tail;
	for (auto &v : g_.get_vertices())
	{
		if (v->vertex_type == cidfg::Vertex::LOOP_VERTEX)
		{
			int parent_id;
			int child_index;
			g_.get_parent(v->id, parent_id, child_index);

			cidfg::HierarchicalInstrVertex v_loop;
			v_loop.coord = v->coord;
			int id_v_loop = g_.add_vertex(v_loop, parent_id, child_index);

			cidfg::LoophInstrVertex v_lh;
			cidfg::LooptInstrVertex v_lt;
			cidfg::HierarchicalInstrVertex v_lb;
			v_lh.coord = v->coord;
			v_lt.coord = v->coord;
			v_lb.coord = v->coord;
			v_lb.is_bulk = true;

			BIR::LoopHeaderInstruction *i_lh = CREATE_OBJECT_B(LoopHeaderInstruction);
			BIR::LoopTailInstruction *i_lt = CREATE_OBJECT_B(LoopTailInstruction);
			i_lh->correspondingLoopTailInst = i_lt;
			i_lh->loopId = static_cast<cidfg::LoopVertex *>(v)->loop_id;
			i_lt->loopId = static_cast<cidfg::LoopVertex *>(v)->loop_id;
			i_lt->corresponding_loop_header_instr = i_lh;

			cidfg::Edge *in0 = g_.get_edge(g_.get_in_edge(v->id, 0));
			cidfg::Edge *in1 = g_.get_edge(g_.get_in_edge(v->id, 1));
			cidfg::Edge *in2 = g_.get_edge(g_.get_in_edge(v->id, 2));

			if (g_.get_vertex(in0->src_id)->vertex_type == cidfg::Vertex::CONST_VERTEX)
			{
				i_lh->startValue = static_cast<cidfg::ConstVertex *>(g_.get_vertex(in0->src_id))->int_data;
				i_lh->isStatic = true;
			}
			else
			{
				LOG(FATAL) << "Unsupported non-constant loop start address!";
			}
			if (g_.get_vertex(in1->src_id)->vertex_type == cidfg::Vertex::CONST_VERTEX)
			{
				i_lt->stepValue = static_cast<cidfg::ConstVertex *>(g_.get_vertex(in1->src_id))->int_data;
			}
			else
			{
				LOG(FATAL) << "Unsupported non-constant loop incrementer!";
			}
			if (g_.get_vertex(in2->src_id)->vertex_type == cidfg::Vertex::CONST_VERTEX)
			{
				i_lh->isStatic = true;
				i_lh->iterationNumber = static_cast<cidfg::ConstVertex *>(g_.get_vertex(in2->src_id))->int_data;
			}
			else
			{
				i_lh->isStatic = false;
				i_lh->iterationNumber = static_cast<BIR::RACCUInstruction *>(static_cast<cidfg::RaccuInstrVertex *>(g_.get_vertex(in2->src_id))->instr)->resultAddress;
			}

			v_lh.instr = i_lh;
			v_lt.instr = i_lt;

			cidfg::HierarchicalVertex *vv = static_cast<cidfg::HierarchicalVertex *>(v);
			for (int i = 0; i < vv->children.size(); i++)
			{
				for (int j = 0; j < vv->children[i].size(); j++)
				{
					v_lb.add_child(i, vv->children[i][j]);
				}
			}

			int id_v_lh = g_.add_vertex(v_lh, id_v_loop, 0);
			int id_v_lt = g_.add_vertex(v_lt, id_v_loop, 0);
			int id_v_lb = g_.add_vertex(v_lb, id_v_loop, 0);

			cidfg::HierarchicalInstrVertex *ptr_v_loop = static_cast<cidfg::HierarchicalInstrVertex *>(g_.get_vertex(id_v_loop));

			cidfg::Edge e0(id_v_lh, 0, id_v_lb, 0, "LH2LB_strong", cidfg::Edge::DEPENDENCY, 1, 1);
			cidfg::Edge e1(id_v_lb, 0, id_v_lt, 0, "LB2LT_strong", cidfg::Edge::DEPENDENCY, 1, INT_MAX);
			g_.add_edge(e0);
			g_.add_edge(e1);

			for (auto &e : g_.get_edges())
			{
				if (e->src_id == v->id)
				{
					e->src_id = id_v_loop;
				}
				if (e->dest_id == v->id)
				{
					e->dest_id = id_v_loop;
				}
			}
			vv->children.clear();
			loop_vertices.insert(v->id);
			loop_hierarchical_vertices.push_back(id_v_loop);
			loop_hierarchical_vertices_header.push_back(id_v_lh);
			loop_hierarchical_vertices_tail.push_back(id_v_lt);
		}
	}

	for (auto &id : loop_vertices)
	{
		g_.del_vertex(id);
	}

	std::set<int> remove_edges;
	vector<cidfg::Edge *> edges = g_.get_edges();
	for (auto &e : edges)
	{
		for (int i = 0; i < loop_hierarchical_vertices.size(); i++)
		{
			if (e->src_id == loop_hierarchical_vertices[i] && e->src_port == 100)
			{
				for (int j = 0; j < loop_hierarchical_vertices.size(); j++)
				{
					if (e->dest_id == loop_hierarchical_vertices[j])
					{
						cidfg::Edge e0(loop_hierarchical_vertices_header[i], e->src_port, loop_hierarchical_vertices_header[j], e->dest_port, "", cidfg::Edge::DEPENDENCY, 0, 0);
						cidfg::Edge e1(loop_hierarchical_vertices_tail[i], e->src_port, loop_hierarchical_vertices_tail[j], e->dest_port, "", cidfg::Edge::DEPENDENCY, 0, 0);
						g_.add_edge(e0);
						g_.add_edge(e1);
						remove_edges.insert(e->id);

						// whatever in shadow vertex should be assign to main vertex
						cidfg::Vertex *v_src = g_.get_vertex(loop_hierarchical_vertices[i]);
						cidfg::Vertex *v_dest = g_.get_vertex(loop_hierarchical_vertices[j]);
						CHECK(v_src->is_hierarchical());
						CHECK(v_dest->is_hierarchical());
						cidfg::HierarchicalVertex *vv_src = static_cast<cidfg::HierarchicalVertex *>(v_src);
						cidfg::HierarchicalVertex *vv_dest = static_cast<cidfg::HierarchicalVertex *>(v_dest);
						for (int k = 0; k < vv_dest->children.size(); k++)
						{
							for (int l = 0; l < vv_dest->children[k].size(); l++)
							{
								vv_src->add_child(k, vv_dest->children[k][l]);
							}
						}
						vv_dest->children.clear();
					}
				}
			}
		}
	}

	for (auto &id : remove_edges)
	{
		g_.del_edge(id);
	}
}
} // namespace codegen
} // namespace vesyla