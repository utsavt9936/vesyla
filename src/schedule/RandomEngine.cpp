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

#include "RandomEngine.hpp"

using namespace boost;

namespace vesyla
{
namespace schedule
{
RandomEngine::RandomEngine()
{
}
RandomEngine::RandomEngine(Descriptor *desc_)
{
}
RandomEngine::~RandomEngine()
{
}

template <class D, class W, class URBG>
void weighted_shuffle(D first, D last, W first_weight, W last_weight, URBG &&g)
{
	while (first != last and first_weight != last_weight)
	{
		std::discrete_distribution<int> dd(first_weight, last_weight);
		auto i = dd(g);
		if (i)
		{
			std::iter_swap(first, std::next(first, i));
			std::iter_swap(first_weight, std::next(first_weight, i));
		}
		++first;
		++first_weight;
	}
}

void my_copy_graph(Graph &g_src_, Graph &g_dest_)
{
	g_dest_.clear();
	std::unordered_map<Graph::vertex_descriptor, Graph::vertex_descriptor> map_src2dest;
	std::unordered_map<Graph::vertex_descriptor, Graph::vertex_descriptor> map_dest2src;
	Graph::vertex_iterator vi, vi_end;
	Graph::edge_iterator ei, ei_end;
	for (tie(vi, vi_end) = vertices(g_src_); vi != vi_end; vi++)
	{
		Graph::vertex_descriptor vd = add_vertex(g_src_[*vi], g_dest_);
		map_src2dest[*vi] = vd;
		map_dest2src[vd] = *vi;
	}
	for (tie(ei, ei_end) = edges(g_src_); ei != ei_end; ei++)
	{
		add_edge(map_src2dest[source(*ei, g_src_)], map_src2dest[target(*ei, g_src_)], g_src_[*ei], g_dest_);
	}
}
bool RandomEngine::schedule_graph(Graph &g_, Rot &global_rot_in_, int &min_end_time_)
{
	std::srand(unsigned(std::time(0)));
	bool flag_changed = false;
	Graph solution_g;
	Rot solution_rot;
	//LOG(DEBUG) << "Random Engine set optimization iteration number to: 100 ";
	for (int i = 0; i < 100; i++)
	{
		Graph g0;
		my_copy_graph(g_, g0);
		Rot rot0 = global_rot_in_;
		int min_end_time0 = min_end_time_;
		if (schedule_graph_trial(g0, rot0, min_end_time0, (100 - i) / 20))
		{
			//LOG(DEBUG) << "Random Engine found a better solution at iteration " << i;
			my_copy_graph(g0, solution_g);
			solution_rot = rot0;
			min_end_time_ = min_end_time0;
			flag_changed = true;
		}
	}
	my_copy_graph(solution_g, g_);
	global_rot_in_ = solution_rot;
	return flag_changed;
}
bool RandomEngine::schedule_graph_trial(Graph &g, Rot &global_rot_in, int &min_end_time, int max_slack)
{
	// Early return if timing of current solution is worse than the known solution
	for (auto &r : global_rot_in)
	{
		for (auto &f : r.second)
		{
			if (f.type() == Frame::PERIOD && f.t1 >= min_end_time)
			{
				return false;
			}
			else if (f.type() == Frame::KEY && f.t1 >= min_end_time)
			{
				return false;
			}
			else if (f.type() == Frame::LOCK && f.t0 >= min_end_time)
			{
				return false;
			}
		}
	}

	// Return if solution is found
	bool flag_all_scheduled = true;
	graph_traits<Graph>::vertex_iterator vi, vi_end;
	for (tie(vi, vi_end) = vertices(g); vi != vi_end; vi++)
	{
		if (g[*vi].scheduled_time == INT_MIN)
		{
			flag_all_scheduled = false;
			break;
		}
	}

	if (flag_all_scheduled)
	{
		int min_end_time_temp = 0;
		for (auto &r : global_rot_in)
		{
			int end_time = (max_element(r.second.begin(), r.second.end(),
																	[](Frame a, Frame b) -> bool {
																		return (a.max_pos() < b.max_pos());
																	}))
												 ->max_pos();
			if (end_time > min_end_time_temp)
			{
				min_end_time_temp = end_time;
			}
		}
		min_end_time = min_end_time_temp;
		return true;
	}

	Graph solution;
	my_copy_graph(g, solution);
	bool flag_solution_found = false;

	vector<Graph::vertex_descriptor> vec_vd;
	vector<int> vec_priority;
	for (tie(vi, vi_end) = vertices(g); vi != vi_end; vi++)
	{
		if (g[*vi].scheduled_time != INT_MIN)
		{
			continue;
		}
		int slack = find_slack(g, *vi, max_slack);
		if (slack <= 0)
		{
			return false;
		}
		vec_priority.push_back(int(exp(-slack) * 10000));
		vec_vd.push_back(*vi);
	}

	// shuffle the ready vector to randomize it considering the priority
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 gen{seed};
	weighted_shuffle(vec_vd.begin(), vec_vd.end(), vec_priority.begin(), vec_priority.end(), gen);

	for (auto vd : vec_vd)
	{
		// check its predecessors
		// find the min and max scheduled time for current vertex
		int min_schedule_time = -g[vd].shift_factor;
		int max_schedule_time = INT_MAX;
		bool flag_predecessor_not_scheduled = false;
		graph_traits<Graph>::in_edge_iterator iei, iei_end;
		for (tie(iei, iei_end) = in_edges(vd, g); iei != iei_end; iei++)
		{
			if (g[source(*iei, g)].scheduled_time == INT_MIN && g[*iei].d_lo > 0)
			{
				flag_predecessor_not_scheduled = true;
				break;
			}
			if (g[source(*iei, g)].scheduled_time != INT_MIN)
			{
				long th = long(g[*iei].d_hi) + long(g[source(*iei, g)].scheduled_time);
				long tl = long(g[*iei].d_lo) + long(g[source(*iei, g)].scheduled_time);
				if (th < max_schedule_time)
				{
					max_schedule_time = th;
				}
				if (tl > min_schedule_time)
				{
					min_schedule_time = tl;
				}
			}
		}
		if (flag_predecessor_not_scheduled)
		{
			continue;
		}

		graph_traits<Graph>::out_edge_iterator oei, oei_end;
		for (tie(oei, oei_end) = out_edges(vd, g); oei != oei_end; oei++)
		{
			if (g[target(*oei, g)].scheduled_time != INT_MIN)
			{
				long tl = long(g[target(*oei, g)].scheduled_time - long(g[*oei].d_hi));
				long th = long(g[target(*oei, g)].scheduled_time - long(g[*oei].d_lo));
				if (th < max_schedule_time)
				{
					max_schedule_time = th;
				}
				if (tl > min_schedule_time)
				{
					min_schedule_time = tl;
				}
			}
		}

		// int min_frame = INT_MAX;
		// for (auto &r : g[vd].rot)
		// {
		// 	for (auto &f : r.second)
		// 	{
		// 		if (f.pos() < min_frame)
		// 		{
		// 			min_frame = f.pos();
		// 		}
		// 	}
		// }

		// if (min_frame < 0)
		// {
		// 	min_schedule_time -= min_frame;
		// }

		if (min_schedule_time > max_schedule_time)
		{
			continue;
		}
		//LOG(DEBUG) << "Schedule vertex11111111111111111111 " << g[vd].name() << " Range [" << min_schedule_time << ", " << max_schedule_time << "]";
		//LOG(DEBUG) << "old ROT" << endl
		//					 << global_rot_in.dump();
		//LOG(DEBUG) << "add ROT" << endl
		//					 << g[vd].rot.dump();
		Rot new_global_rot = global_rot_in;
		int schedule_time = new_global_rot.merge_and_verify(g[vd].rot, min_schedule_time, max_schedule_time);
		if (schedule_time == INT_MIN)
		{
			continue;
		}

		Graph new_g;
		my_copy_graph(g, new_g);
		new_g[vd].scheduled_time = schedule_time;
		if (!schedule_graph_trial(new_g, new_global_rot, min_end_time, max_slack))
		{
			//continue;
			// directly return
			return false;
		}

		// found a solution
		flag_solution_found = true;
		graph_traits<Graph>::vertex_iterator vii, vii_end;
		for (tie(vii, vii_end) = vertices(solution); vii != vii_end; vii++)
		{
			solution[*vii].scheduled_time = new_g[*vii].scheduled_time;
		}

		break;
	}
	graph_traits<Graph>::vertex_iterator vii, vii_end;
	for (tie(vii, vii_end) = vertices(solution); vii != vii_end; vii++)
	{
		g[*vii].scheduled_time = solution[*vii].scheduled_time;
	}
	return flag_solution_found;
}

int RandomEngine::find_slack(Graph &g_, Graph::vertex_descriptor vd_, int max_slack_)
{
	Graph::in_edge_iterator ei, ei_end;
	int min_slack = INT_MAX;
	for (tie(ei, ei_end) = in_edges(vd_, g_); ei != ei_end; ei++)
	{
		long slack = INT_MAX;
		int src_time = g_[source(*ei, g_)].scheduled_time;
		if (src_time != INT_MAX)
		{
			int max_delay = g_[*ei].d_hi;
			if (max_delay != INT_MAX)
			{
				slack = long(src_time) + long(max_delay);
				slack = slack > max_slack_ ? max_slack_ : slack;
			}
			else
			{
				slack = max_slack_;
			}
		}
		else
		{
			slack = max_slack_;
		}
		if (min_slack > slack)
		{
			min_slack = slack;
		}
	}
	return min_slack;
}

} // namespace schedule
} // namespace vesyla