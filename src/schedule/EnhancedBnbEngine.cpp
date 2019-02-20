#include "EnhancedBnbEngine.hpp"

using namespace boost;

namespace vesyla
{
namespace schedule
{
EnhancedBnbEngine::EnhancedBnbEngine()
{
}
EnhancedBnbEngine::EnhancedBnbEngine(Descriptor *desc_)
{
}
EnhancedBnbEngine::~EnhancedBnbEngine()
{
}
bool EnhancedBnbEngine::schedule_graph(Graph &g, Rot &global_rot_in, int &min_end_time)
{
	// Early return if timing of current solution is worse than the known solution
	for (auto &r : global_rot_in)
	{
		for (auto &f : r.second)
		{
			if (f.pos() >= min_end_time)
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
		if (g[*vi].scheduled_time < 0)
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

	// trial schedule to find out the schedule cost
	Graph solution;
	copy_graph(g, solution);
	bool flag_solution_found = false;
	int index = 0;
	struct PriorityInfo
	{
		graph_traits<Graph>::vertex_descriptor v; // vertex descriptor
		float c;																	// cost
	};
	vector<PriorityInfo> priority_info_list(num_vertices(g));
	for (tie(vi, vi_end) = vertices(g); vi != vi_end; vi++, index++)
	{
		priority_info_list[index].v = *vi;
		priority_info_list[index].c = FLT_MAX;
		if (g[*vi].scheduled_time >= 0)
		{
			if (g[*vi].name() == "__temp1")
			{
				LOG(DEBUG) << "RETURN HERE";
			}
			continue;
		}
		// check its predecessors
		// find the min and max scheduled time for current vertex
		int min_schedule_time = 0;
		int max_schedule_time = INT_MAX;
		bool flag_predecessor_not_scheduled = false;
		graph_traits<Graph>::in_edge_iterator iei, iei_end;
		for (tie(iei, iei_end) = in_edges(*vi, g); iei != iei_end; iei++)
		{
			if (g[source(*iei, g)].scheduled_time < 0 && g[*iei].d_lo > 0)
			{
				flag_predecessor_not_scheduled = true;
				break;
			}
			if (g[source(*iei, g)].scheduled_time >= 0)
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
			if (g[*vi].name() == "__temp1")
			{
				LOG(DEBUG) << "RETURN HERE";
			}
			continue;
		}
		graph_traits<Graph>::out_edge_iterator oei, oei_end;
		for (tie(oei, oei_end) = out_edges(*vi, g); oei != oei_end; oei++)
		{
			if (g[target(*oei, g)].scheduled_time >= 0)
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

		if (min_schedule_time > max_schedule_time)
		{
			if (g[*vi].name() == "__temp1")
			{
				LOG(DEBUG) << "RETURN HERE";
			}
			continue;
		}

		Rot new_global_rot = global_rot_in;
		int schedule_time = new_global_rot.merge_and_verify(g[*vi].rot, min_schedule_time, max_schedule_time);

		if (schedule_time < min_schedule_time)
		{

			continue;
		}
		if (g[*vi].name() == "ROOT_307_0")
		{
			LOG(DEBUG) << "RETURN HERE: min=" << min_schedule_time << ", max=" << max_schedule_time << ", schedule=" << schedule_time;
			cout << global_rot_in.dump() << endl;
			cout << g[*vi].rot.dump() << endl;
		}
		int max_time = schedule_time;
		bool flag_found_a_key = false;
		for (auto &pair : g[*vi].rot)
		{
			for (auto f : pair.second)
			{
				if (max_time < f.max_pos() + schedule_time)
				{
					max_time = f.max_pos() + schedule_time;
				}
				if (f.type() == 1)
				{
					flag_found_a_key = true;
					max_time = 0;
					break;
				}
			}
			if (flag_found_a_key)
			{
				break;
			}
		}
		priority_info_list[index].c = max_time;
	}

	std::sort(priority_info_list.begin(), priority_info_list.end(),
						[](PriorityInfo const a, PriorityInfo const b) { return a.c < b.c; });

	for (auto &pi : priority_info_list)
	{
		cout << "(" << g[pi.v].name() << ":" << pi.c << "), ";
	}
	cout << endl
			 << "----------------------------------------------" << endl;

	// Real schedule
	for (auto &pi : priority_info_list)
	{
		int vertex = pi.v;
		float cost = pi.c;
		if (cost == FLT_MAX)
		{
			flag_solution_found = false;
			break;
		}
		// check its predecessors
		// find the min and max scheduled time for current vertex
		int min_schedule_time = 0;
		int max_schedule_time = INT_MAX;
		bool flag_predecessor_not_scheduled = false;
		graph_traits<Graph>::in_edge_iterator iei, iei_end;
		for (tie(iei, iei_end) = in_edges(vertex, g); iei != iei_end; iei++)
		{
			if (g[source(*iei, g)].scheduled_time < 0 && g[*iei].d_lo > 0)
			{
				flag_predecessor_not_scheduled = true;
				break;
			}
			if (g[source(*iei, g)].scheduled_time >= 0)
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
			flag_solution_found = false;
			break;
		}
		graph_traits<Graph>::out_edge_iterator oei, oei_end;
		for (tie(oei, oei_end) = out_edges(vertex, g); oei != oei_end; oei++)
		{
			if (g[target(*oei, g)].scheduled_time >= 0)
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

		if (min_schedule_time > max_schedule_time)
		{
			flag_solution_found = false;
			break;
		}
		cout << "SCHEDULE " << g[vertex].name() << endl;
		Rot new_global_rot = global_rot_in;
		int schedule_time = new_global_rot.merge_and_verify(g[vertex].rot, min_schedule_time, max_schedule_time);

		if (schedule_time < min_schedule_time)
		{
			flag_solution_found = false;
			break;
		}
		Graph new_g;
		copy_graph(g, new_g);
		new_g[vertex].scheduled_time = schedule_time;
		if (!schedule_graph(new_g, new_global_rot, min_end_time))
		{
			flag_solution_found = false;
			break;
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
} // namespace schedule
} // namespace vesyla