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

#include "ConstraintProgrammingEngine.hpp"

namespace vesyla
{
namespace schedule
{
ConstraintProgrammingEngine::ConstraintProgrammingEngine()
{
}
ConstraintProgrammingEngine::ConstraintProgrammingEngine(Descriptor *desc_)
{
}
ConstraintProgrammingEngine::~ConstraintProgrammingEngine()
{
}
bool ConstraintProgrammingEngine::schedule_graph(Graph &g_, Rot &global_rot_in_, int &min_end_time_)
{
	// create model and search engine
	std::unordered_map<string, int> res_map;
	int i = 0;
	Graph::vertex_iterator vi, vi_end;
	for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++)
	{
		Rot rot = g_[*vi].rot;
		for (auto &r : rot)
		{
			if (res_map.find(r.first) == res_map.end())
			{
				res_map[r.first] = i;
				i++;
			}
		}
	}
	Solver *m = new Solver(g_, global_rot_in_, min_end_time_, 10000);
	Gecode::BAB<Solver> e(m);
	delete m;
	// search and print all solutions
	if (Solver *s = e.next())
	{
		s->fill_scheduled_time(g_);
		Graph::vertex_iterator vi, vi_end;
		int i = 0;
		for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++)
		{
			global_rot_in_.merge(g_[*vi].rot, g_[*vi].scheduled_time);
		}
		CHECK(global_rot_in_.verify());
		delete s;
		return true;
	}
	return false;
}

Solver::Solver(Graph &g_, Rot &global_rot_in_, int &min_end_time_, int max_scheduled_time) : _scheduled_time_list(*this, num_vertices(g_), 0, max_scheduled_time), _latency(*this, 0, max_scheduled_time)
{
	// Cost function
	Gecode::max(*this, _scheduled_time_list, _latency);

	Graph::vertex_iterator vi, vi_end;
	int i = 0;
	for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++)
	{
		_vertex_map[g_[*vi].name()] = i;
	}
	Graph::edge_iterator ei, ei_end;
	for (tie(ei, ei_end) = edges(g_); ei != ei_end; ei++)
	{
		string src_name = g_[source(*ei, g_)].name();
		string dest_name = g_[target(*ei, g_)].name();
		int src_idx = _vertex_map[src_name];
		int dest_idx = _vertex_map[dest_name];

		if (g_[*ei].d_lo != INT_MIN && g_[*ei].d_hi != INT_MAX)
		{
			Gecode::rel(*this, _scheduled_time_list[dest_idx] - _scheduled_time_list[src_idx] == g_[*ei].d_lo);
		}
		else if (g_[*ei].d_lo != INT_MIN)
		{
			Gecode::rel(*this, _scheduled_time_list[dest_idx] - _scheduled_time_list[src_idx] >= g_[*ei].d_lo);
		}
		else if (g_[*ei].d_hi != INT_MAX)
		{
			Gecode::rel(*this, _scheduled_time_list[dest_idx] - _scheduled_time_list[src_idx] <= g_[*ei].d_hi);
		}
	}

	std::unordered_map<string, int> res_map;
	i = 0;
	for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++)
	{
		Rot rot = g_[*vi].rot;
		for (auto &r : rot)
		{
			if (res_map.find(r.first) == res_map.end())
			{
				res_map[r.first] = i;
				i++;
			}
		}
	}

	std::unordered_map<string, vector<vector<int>>> occupation;
	for (auto &r : res_map)
	{
		occupation[r.first] = {};
	}
	std::unordered_map<string, vector<int>> occupation_0;
	for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++)
	{
		Rot rot = g_[*vi].rot;
		for (auto &r : rot)
		{
			for (auto &f : r.second)
			{
				if (f.type() == 1)
				{ // key
					string signature = r.first + "#!#" + to_string(f.sn);
					if (occupation_0.find(signature) != occupation_0.end())
					{
						occupation_0[signature][2] = _vertex_map[g_[*vi].name()];
						occupation_0[signature][3] = f.t1;
					}
					else
					{
						occupation_0[signature] = {INT_MIN, INT_MIN, _vertex_map[r.first], f.t1};
					}
				}
				else if (f.type() == 2)
				{ // lock
					string signature = r.first + "#!#" + to_string(f.sn);
					if (occupation_0.find(signature) != occupation_0.end())
					{
						occupation_0[signature][0] = _vertex_map[g_[*vi].name()];
						occupation_0[signature][1] = f.t0;
					}
					else
					{
						occupation_0[signature] = {_vertex_map[g_[*vi].name()], f.t0, INT_MAX, INT_MAX};
					}
				}
				else if (f.type() == 3)
				{ // normal
					string signature = r.first;
					occupation[signature].push_back({_vertex_map[g_[*vi].name()], f.t0, _vertex_map[g_[*vi].name()], f.t1});
				}
			}
		}
	}
	for (auto r : occupation_0)
	{
		string resource_name = r.first;

		string delimiter = "#!#";
		resource_name = resource_name.substr(0, resource_name.find(delimiter));
		occupation[resource_name].push_back(r.second);
	}

	for (auto &r : occupation)
	{
		Gecode::IntVarArgs start_time_array(*this, r.second.size(), 0, max_scheduled_time);
		Gecode::IntVarArgs end_time_array(*this, r.second.size(), 0, max_scheduled_time);
		Gecode::IntVarArgs delay_array(*this, r.second.size(), 0, max_scheduled_time);
		for (int j = 0; j < r.second.size(); j++)
		{
			Gecode::rel(*this, _scheduled_time_list[r.second[j][0]] + r.second[j][1] == start_time_array[j]);
			Gecode::rel(*this, _scheduled_time_list[r.second[j][2]] + r.second[j][3] + 1 == end_time_array[j]);
			Gecode::rel(*this, end_time_array[j] - start_time_array[j] == delay_array[j]);
		}
		Gecode::unary(*this, start_time_array, delay_array, end_time_array, Gecode::IPL_DEF);
	}

	// post branching
	Gecode::branch(*this, _scheduled_time_list, Gecode::INT_VAR_SIZE_MIN(), Gecode::INT_VAL_MIN());
}

// search support
Solver::Solver(Solver &s) : Gecode::IntMinimizeSpace(s)
{
	_scheduled_time_list.update(*this, s._scheduled_time_list);
	_vertex_map = s._vertex_map;
}
Gecode::Space *Solver::copy(void)
{
	return new Solver(*this);
}
// print solution
string Solver::solution_to_str(void) const
{
	std::stringstream buffer;
	buffer << _scheduled_time_list;
	return buffer.str();
}

// cost function
Gecode::IntVar Solver::cost(void) const
{
	return _latency;
}

void Solver::constrain(const Gecode::Space &b_)
{
	const Solver &b = static_cast<const Solver &>(b_);
	Gecode::rel(*this, _latency < b._latency);
}

void Solver::fill_scheduled_time(Graph &g_)
{
	Graph::vertex_iterator vi, vi_end;
	int i = 0;
	for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++)
	{
		g_[*vi].scheduled_time = _scheduled_time_list[i].val();
	}
}

} // namespace schedule
} // namespace vesyla