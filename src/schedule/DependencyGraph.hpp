#ifndef __VESYLA_SCHEDULE_DEPENDENCY_GRAPH_HPP__
#define __VESYLA_SCHEDULE_DEPENDENCY_GRAPH_HPP__

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include "util/Common.hpp"

using json = nlohmann::json;
using namespace std;

namespace vesyla
{
namespace schedule
{

class DependencyGraph
{
public:
	enum LinkType
	{
		SOFT_LINK_DEPENDENCY,
		HARD_LINK_DEPENDENCY
	};

	enum NodeType
	{
		HIRARICHICAL_NODE,
		PACK_NODE,
		LEAF_NODE
	};

	struct Vertex
	{
		int id;
		string name;
		int start;
		map<string, vector<int>> resource;
		int pack_id;
		int pack_offset;
		int offset;
		int org_start;
		vector<Vertex> children;
		NodeType node_type;
		std::shared_ptr<DependencyGraph> subgraph;
		std::shared_ptr<DependencyGraph> subgraph_extra;

		bool active;

		Vertex(int _id = 0, string _name = "", map<string, vector<int>> _resource = {}, NodeType _node_type = LEAF_NODE) : name(_name), resource(_resource), node_type(_node_type)
		{
			id = _id;
			start = 0;
			pack_id = -1;
			pack_offset = -1;
			offset = 0;
			org_start = 0;
			if (_node_type == HIRARICHICAL_NODE)
			{
				subgraph = make_shared<DependencyGraph>();
				subgraph_extra = make_shared<DependencyGraph>();
			}
			else
			{
				subgraph = NULL;
				subgraph_extra = NULL;
			}

			active = true;
		}
		Vertex(json j_)
		{
			load_from_json(j_);
		}
		void load_from_json(json j_)
		{
			id = j_["id"];
			name = j_["name"];
			for (auto it = j_["resource"].begin(); it != j_["resource"].end(); it++)
			{
				vector<int> vec = {it.value()[0], it.value()[1]};
				resource[it.key()] = vec;
			}
			node_type = j_["node_type"];
			start = 0;
			pack_id = -1;
			pack_offset = -1;
			if (node_type == HIRARICHICAL_NODE)
			{
				subgraph = make_shared<DependencyGraph>(j_["subgraph"]);
				if (!j_["subgraph_extra"].empty())
				{
					subgraph_extra = make_shared<DependencyGraph>(j_["subgraph_extra"]);
				}
				else
				{
					subgraph_extra = NULL;
				}
			}
			else
			{
				subgraph = NULL;
				subgraph_extra = NULL;
			}
		}

		void convert_to_hirarichical()
		{
			if (node_type != HIRARICHICAL_NODE)
			{
				node_type = HIRARICHICAL_NODE;
				subgraph = make_shared<DependencyGraph>();
				subgraph_extra = make_shared<DependencyGraph>();
			}
		}

		void schedule()
		{
			switch (node_type)
			{
			case HIRARICHICAL_NODE:
			{
				for (auto &v : subgraph->_vertex_list)
				{
					v.schedule();
				}
				subgraph->schedule();
				// update resource usage for node according to its subgraph
				int min_end_time_1 = 0;
				int min_end_time_2 = 0;
				for (auto &v : subgraph->_vertex_list)
				{
					for (auto &res : v.resource)
					{
						if (min_end_time_1 < (v.start + res.second[1]))
						{
							min_end_time_1 = (v.start + res.second[1]);
						}
						if (resource.find(res.first) == resource.end())
						{
							resource[res.first] = {0, 0};
						}
					}
				}

				if (subgraph_extra)
				{
					for (auto &v : subgraph_extra->_vertex_list)
					{
						v.schedule();
					}
					subgraph_extra->schedule();
					// update resource usage for node according to its subgraph
					for (auto &v : subgraph_extra->_vertex_list)
					{
						for (auto &res : v.resource)
						{
							if (min_end_time_2 < (v.start + res.second[1]))
							{
								min_end_time_2 = (v.start + res.second[1]);
							}
							if (resource.find(res.first) == resource.end())
							{
								resource[res.first] = {0, 0};
							}
						}
					}
				}

				if (min_end_time_2 > min_end_time_1)
				{
					min_end_time_1 = min_end_time_2;
				}

				cout << "min_end_time of " << name << " = " << min_end_time_1 << endl;
				for (auto &res : resource)
				{
					res.second = {0, min_end_time_1};
				}
				break;
			}
			case PACK_NODE:
				break;
			case LEAF_NODE:
				break;
			default:
				break;
			}
		}

		void update_abs_start(int &start_in)
		{
			if (node_type == HIRARICHICAL_NODE)
			{
				if (subgraph != NULL)
				{
					for (auto &v : subgraph->_vertex_list)
					{
						v.update_abs_start(start_in);
					}
				}
				if (subgraph_extra != NULL)
				{
					for (auto &v : subgraph_extra->_vertex_list)
					{
						v.update_abs_start(start_in);
					}
				}
			}
			if (node_type == LEAF_NODE)
			{
				org_start = start;
				start += start_in;
			}
		}

		void update_abs_offset(int &offset_in)
		{
			if (node_type == HIRARICHICAL_NODE)
			{
				if (subgraph != NULL)
				{
					for (auto &v : subgraph->_vertex_list)
					{
						v.start += start;
						v.update_abs_offset(offset_in);
					}
					for (auto &res : resource)
					{
						offset_in += (res.second[1] + 1);
						break;
					}
				}
				if (subgraph_extra != NULL)
				{
					for (auto &v : subgraph_extra->_vertex_list)
					{
						v.start += start;
						v.update_abs_offset(offset_in);
					}
					for (auto &res : resource)
					{
						offset_in += (res.second[1] + 1);
						break;
					}
				}
			}
			if (node_type == LEAF_NODE)
			{
				offset = org_start + offset_in;
			}
		}
	};

	struct Edge
	{
		int src_id;
		int dest_id;
		LinkType link_type;
		int distance;

		Edge(int _src_id = -1, int _dest_id = -1, LinkType _link_type = SOFT_LINK_DEPENDENCY, int _distance = -1) : src_id(_src_id), dest_id(_dest_id), link_type(_link_type), distance(_distance) {}

		Edge(json j_)
		{
			load_from_json(j_);
		}
		void load_from_json(json j_)
		{
			src_id = j_["src_id"];
			dest_id = j_["dest_id"];
			link_type = j_["link_type"];
			distance = j_["distance"];
		}
	};

public:
	int start;
	map<string, vector<int>> resource;

private:
	vector<Vertex> _vertex_list;
	vector<Edge> _edge_list;

public:
	DependencyGraph()
	{
		start = 0;
	};
	DependencyGraph(json j_)
	{
		load_from_json(j_);
	}
	void load_from_json(json j_)
	{
		start = 0;
		if (j_.find("vertex") != j_.end())
		{
			for (auto &v : j_["vertex"])
			{
				Vertex vv(v);
				_vertex_list.push_back(vv);
			}
		}
		if (j_.find("edge") != j_.end())
		{
			for (auto &e : j_["edge"])
			{
				Edge ee(e);
				_edge_list.push_back(ee);
			}
		}
	}
	~DependencyGraph(){};
	void add_vertex(Vertex &_v);
	bool add_edge(Edge &_e);
	void dump();
	Vertex &find_vertex(int _id);
	vector<int> find_predecessors(int _id);
	vector<int> find_successors(int _id);
	void calculate_pack_offset(int _id);
	void assign_packs();
	void schedule();
	void try_schedule_one(vector<Vertex> scheduled_vertex_set_in, vector<Vertex> unscheduled_vertex_set_in, map<string, int> clock_in, vector<Vertex> &solution_out, int &min_end_time, vector<vector<Vertex>> &solution_list_out);
	void schedule_one_vertex(Vertex v_in, map<string, int> c_in, int min_schedule_time, Vertex &v_out, map<string, int> &c_out);
	vector<Vertex> &vertex_list()
	{
		return _vertex_list;
	}
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_DEPENDENCY_GRAPH_HPP__
