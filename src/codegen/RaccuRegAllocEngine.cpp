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

#include "RaccuRegAllocEngine.hpp"

using namespace vesyla::cidfg;

namespace vesyla
{
namespace codegen
{
void RaccuRegAllocEngine::transform(CidfgGraph &g_)
{
}


































void RaccuRegAllocEngine::create_graph(CidfgGraph &g_, Graph &g0_, VIR::Coordinate coord_, std::unordered_map<int, Graph::vertex_descriptor> &map_g2g0_, std::unordered_map<Graph::vertex_descriptor, int> &map_g02g_)
{
	std::unordered_map<int, int> selected_vertex;
	for (auto &v : g_.get_vertices())
	{
		if (v->vertex_type == Vertex::COMPUTATION_VERTEX)
		{
			ComputationVertex *vv = static_cast<ComputationVertex *>(v);
			if (!(vv->is_on_dpu) && vv->coord == coord_)
			{
				selected_vertex[v->id] = 0; // type 0 vertex: computation
			}
		}
		else if (v->vertex_type == Vertex::READ_AND_INDEX_VERTEX || v->vertex_type == Vertex::WRITE_AND_INDEX_VERTEX || v->is_sink())
		{
			if (v->coord == coord_)
			{
				selected_vertex[v->id] = 1; // type 1 vertex: sink
			}
		}
	}

	Graph g1;
	std::unordered_map<int, Graph::vertex_descriptor> map_g2g1;
	std::unordered_map<Graph::vertex_descriptor, int> map_g12g;
	for (auto &sv : selected_vertex)
	{
		Graph::vertex_descriptor vd = add_vertex(sv.second, g1);
		map_g2g1[sv.first] = vd;
		map_g12g[vd] = sv.first;
	}

	for (auto &e : g_.get_edges())
	{
		if (e->edge_type == Edge::DEPENDENCY)
		{
			continue;
		}
		if (selected_vertex.find(e->src_id) != selected_vertex.end() && selected_vertex.find(e->dest_id) != selected_vertex.end())
		{
			add_edge(map_g2g1[e->src_id], map_g2g1[e->dest_id], e->var_name, g1);
		}
	}

	Graph::vertex_iterator vi, vi_end;
	for (tie(vi, vi_end) = vertices(g1); vi != vi_end; vi++)
	{
		if (in_degree(*vi, g1) == 0 && out_degree(*vi, g1) == 0)
		{
			selected_vertex.erase(map_g12g[*vi]);
		}
	}

	for (auto &sv : selected_vertex)
	{
		Graph::vertex_descriptor vd = add_vertex(sv.second, g0_);
		map_g2g0_[sv.first] = vd;
		map_g02g_[vd] = sv.first;
	}

	for (auto &e : g_.get_edges())
	{
		if (e->edge_type == Edge::DEPENDENCY)
		{
			continue;
		}
		if (selected_vertex.find(e->src_id) != selected_vertex.end() && selected_vertex.find(e->dest_id) != selected_vertex.end())
		{
			add_edge(map_g2g0_[e->src_id], map_g2g0_[e->dest_id], e->var_name, g0_);
		}
	}
}

int RaccuRegAllocEngine::pre_assign(Graph &g0_)
{
	std::unordered_map<string, int> map_pre_assign;
	Graph::edge_iterator e, e_end;
	for (tie(e, e_end) = edges(g0_); e != e_end; e++)
	{
		if (strncmp(g0_[*e].c_str(), "temp_", strlen("temp_")) == 0)
		{
			continue;
		}
		if (map_pre_assign.find(g0_[*e]) != map_pre_assign.end())
		{
			g0_[*e] = "RR_" + to_string(map_pre_assign[g0_[*e]]);
		}
		else
		{
			int id = map_pre_assign.size();
			map_pre_assign[g0_[*e]] = id;
			g0_[*e] = "RR_" + to_string(id);
		}
	}
	return map_pre_assign.size();
}

void RaccuRegAllocEngine::pre_group(Graph &g0_)
{
	int group_counter = 0;
	std::unordered_map<string, string> edge_group;
	Graph::vertex_iterator vi, vi_end;
	for (tie(vi, vi_end) = vertices(g0_); vi != vi_end; vi++)
	{
		if (g0_[*vi] == 0)
		{
			Graph::out_edge_iterator oei, oei_end;
			for (tie(oei, oei_end) = out_edges(*vi, g0_); oei != oei_end; oei++)
			{
				if (strncmp(g0_[*oei].c_str(), "temp_", strlen("temp_")) == 0)
				{
					if (edge_group.find(g0_[*oei]) != edge_group.end())
					{
						g0_[*oei] = edge_group[g0_[*oei]];
					}
					else
					{
						edge_group[g0_[*oei]] = "GROUP_" + to_string(group_counter);
						g0_[*oei] = "GROUP_" + to_string(group_counter);
					}
				}
			}
			group_counter++;
		}
	}
}

} // namespace codegen
} // namespace vesyla