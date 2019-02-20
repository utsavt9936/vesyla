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

#include "DependencyAnalyzeEngine.hpp"

using namespace vesyla::cidfg;

namespace vesyla
{
namespace feopt
{
void DependencyAnalyzeEngine::transform(CidfgGraph &g_)
{
	for (auto &e : g_.get_edges())
	{
		if (e->edge_type != Edge::DEPENDENCY)
		{
			continue;
		}
		if (e->var_name != "WAW" && e->var_name != "WAR")
		{
			continue;
		}
		bool flag_strong = true;
		if (g_.get_vertex(e->dest_id)->vertex_type == Vertex::WRITE_AND_INDEX_VERTEX)
		{
			vector<int> src_addr_info = get_addr_info(g_, e->src_id);
			vector<int> dest_addr_info = get_addr_info(g_, e->dest_id);

			if (src_addr_info.size() == 5 && dest_addr_info.size() == 5)
			{
				if (src_addr_info[1] == dest_addr_info[1] && src_addr_info[2] == dest_addr_info[2] && src_addr_info[3] == dest_addr_info[3] && src_addr_info[4] == dest_addr_info[4])
				{
					flag_strong = false;
					e->d_lo = dest_addr_info[0] - src_addr_info[0] + 1;
				}
				else if ((src_addr_info[2] == 1 && src_addr_info[4] == 1) || (dest_addr_info[2] == 1 && dest_addr_info[4] == 1))
				{
					flag_strong = false;
					e->d_lo = dest_addr_info[0] - src_addr_info[0] + 1;
				}
			}
		}
		if (flag_strong)
		{
			e->var_name = e->var_name + "_strong";
		}
		else
		{
			e->var_name = e->var_name + "_weak";
		}
	}
}

vector<int> DependencyAnalyzeEngine::get_addr_info(CidfgGraph &g_, int vid_)
{
	if (g_.get_vertex(vid_)->vertex_type != Vertex::WRITE_AND_INDEX_VERTEX && g_.get_vertex(vid_)->vertex_type != Vertex::READ_AND_INDEX_VERTEX)
	{
		return {};
	}

	int start_port = 1;
	if (g_.get_vertex(vid_)->vertex_type == Vertex::WRITE_AND_INDEX_VERTEX)
	{
		start_port = 2;
	}
	else
	{
		start_port = 1;
	}

	vector<int> info;
	Vertex *vv;
	vv = g_.get_vertex(g_.get_edge(g_.get_in_edge(vid_, start_port++))->src_id);
	if (vv->vertex_type == cidfg::Vertex::CONST_VERTEX)
	{
		info.push_back(static_cast<cidfg::ConstVertex *>(vv)->int_data);
	}
	else
	{
		return {};
	}
	vv = g_.get_vertex(g_.get_edge(g_.get_in_edge(vid_, start_port++))->src_id);
	if (vv->vertex_type == cidfg::Vertex::CONST_VERTEX)
	{
		info.push_back(static_cast<cidfg::ConstVertex *>(vv)->int_data);
	}
	else
	{
		return {};
	}
	vv = g_.get_vertex(g_.get_edge(g_.get_in_edge(vid_, start_port++))->src_id);
	if (vv->vertex_type == cidfg::Vertex::CONST_VERTEX)
	{
		info.push_back(static_cast<cidfg::ConstVertex *>(vv)->int_data);
	}
	else
	{
		return {};
	}
	vv = g_.get_vertex(g_.get_edge(g_.get_in_edge(vid_, start_port++))->src_id);
	if (vv->vertex_type == cidfg::Vertex::CONST_VERTEX)
	{
		info.push_back(static_cast<cidfg::ConstVertex *>(vv)->int_data);
	}
	else
	{
		return {};
	}
	vv = g_.get_vertex(g_.get_edge(g_.get_in_edge(vid_, start_port++))->src_id);
	if (vv->vertex_type == cidfg::Vertex::CONST_VERTEX)
	{
		info.push_back(static_cast<cidfg::ConstVertex *>(vv)->int_data);
	}
	else
	{
		return {};
	}
	return info;
}

} // namespace feopt
} // namespace vesyla