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

#include "CleanEngine.hpp"

using namespace vesyla::cidfg;
using namespace boost;

namespace vesyla
{
namespace feopt
{

void CleanEngine::transform(CidfgGraph &g_)
{
	vector<cidfg::Edge> dependency_edges;
	for (auto &e : g_.get_edges())
	{
		if (e->edge_type == cidfg::Edge::DEPENDENCY)
		{
			dependency_edges.push_back(*e);
			g_.del_edge(e->id);
		}
	}

	typedef boost::adjacency_list<vecS, vecS, directedS, cidfg::Vertex *, cidfg::Edge *> Graph;
	Graph g0, g1;
	map<int, int> vertex_cidfg2graph;
	map<int, int> vertex_graph2cidfg;
	for (auto &v : g_.get_vertices())
	{
		int id = add_vertex(v, g0);
		vertex_cidfg2graph[v->id] = id;
		vertex_graph2cidfg[id] = v->id;
	}
	for (auto &e : g_.get_edges())
	{
		add_edge(vertex_cidfg2graph[e->src_id], vertex_cidfg2graph[e->dest_id], e, g0);
	}

	transitive_closure(g0, g1);

	std::set<int> removed_vertices;
	for (auto &v : g_.get_vertices())
	{
		if (v->is_sink() || v->is_hierarchical() || v->is_instr())
		{
			continue;
		}
		bool flag_is_needed = false;
		graph_traits<Graph>::out_edge_iterator oei, oei_end;
		for (tie(oei, oei_end) = out_edges(vertex_cidfg2graph[v->id], g1); oei != oei_end; oei++)
		{
			Vertex *vv = g_.get_vertex(vertex_graph2cidfg[target(*oei, g1)]);
			if (vv->is_sink() || vv->is_hierarchical() || vv->is_instr())
			{
				flag_is_needed = true;
				break;
			}
		}
		if (flag_is_needed == false)
		{
			removed_vertices.insert(v->id);
		}
	}

	for (auto &id : removed_vertices)
	{
		g_.del_vertex(id);
	}

	for (auto &e : dependency_edges)
	{
		if (removed_vertices.find(e.src_id) == removed_vertices.end() && removed_vertices.find(e.dest_id) == removed_vertices.end())
		{
			g_.add_edge(e);
		}
	}
}

} // namespace feopt
} // namespace vesyla