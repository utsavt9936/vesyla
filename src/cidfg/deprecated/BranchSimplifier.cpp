#include "BranchSimplifier.hpp"
#include <boost/algorithm/string.hpp>

using namespace boost;

namespace vesyla
{
namespace cidfg
{

BranchSimplifier::BranchSimplifier() {}
BranchSimplifier::~BranchSimplifier() {}

void BranchSimplifier::simplify(CidfgGraph &new_g_, CidfgGraph &g_)
{
	Graph g0 = create_graph(g_);
	graph_traits<Graph>::vertex_iterator vi, vi_end;
	for (tie(vi, vi_end) = vertices(g0); vi != vi_end; vi++)
	{
		if (g0[*vi]->vertex_type == Vertex::SINK_VERTEX || g0[*vi]->is_hierarchical())
		{
			EdgeProperty vr = cal_var_record(g0, *vi);
		}
	}
	std::unordered_map<boost::graph_traits<Graph>::vertex_descriptor, int> vertex_map;
	VarTable vt;
	construct_cidfg_graph(new_g_, g0, UINT_MAX, vertex_map, vt);
}

Graph BranchSimplifier::create_graph(CidfgGraph &g_)
{
	Graph g1;
	map<int, boost::graph_traits<Graph>::vertex_descriptor> gdict1;
	for (Vertex *v : g_.get_vertices())
	{
		auto vi = add_vertex(v, g1);
		gdict1[v->id] = vi;
	}
	for (Edge *e : g_.get_edges())
	{
		EdgeProperty vr;
		vr.src_port = e->src_port;
		vr.dest_port = e->dest_port;
		vr.edge = *e;
		add_edge(gdict1[e->src_id], gdict1[e->dest_id], vr, g1);
	}
	return g1;
}

// int BranchSimplifier::construct_cidfg_graph(CidfgGraph &g_, Graph &g0_)
// {
// 	graph_traits<Graph>::edge_iterator ei, ei_end;
// 	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> UGraph;
// 	UGraph ug0(num_vertices(g0_));
// 	for (tie(ei, ei_end) = edges(g0_); ei != ei_end; ++ei)
// 	{
// 		add_edge(source(*ei, g0_), target(*ei, g0_), ug0);
// 		add_edge(target(*ei, g0_), source(*ei, g0_), ug0);
// 	}
// 	std::vector<int> component(boost::num_vertices(ug0));
// 	int num_components = boost::connected_components(ug0, &component[0]);

// 	for(auto& c : num_components){
// 		// create a DAG based on this color
// 		Graph g1;

// 	}
// }

int BranchSimplifier::construct_cidfg_graph(CidfgGraph &g_, Graph &g0_, boost::graph_traits<Graph>::vertex_descriptor v_, std::unordered_map<boost::graph_traits<Graph>::vertex_descriptor, int> &vertex_map_, VarTable &vt_, std::unordered_map<string, int> iterator_set_)
{
	if (v_ == UINT_MAX)
	{
		// Create a map for old id to descriptor in g0
		std::unordered_map<int, boost::graph_traits<Graph>::vertex_descriptor> vertex_id_map;
		graph_traits<Graph>::vertex_iterator vi, vi_end;
		for (tie(vi, vi_end) = vertices(g0_); vi != vi_end; vi++)
		{
			vertex_id_map[g0_[*vi]->id] = *vi;
		}

		std::unordered_map<string, int> iterator_set;
		for (tie(vi, vi_end) = vertices(g0_); vi != vi_end; vi++)
		{
			if (g0_[*vi]->vertex_type == Vertex::LOOP_VERTEX)
			{
				LoopVertex *vv = static_cast<LoopVertex *>(g0_[*vi]);
				iterator_set[vv->iterator_name] = vv->loop_id;
			}
		}

		for (tie(vi, vi_end) = vertices(g0_); vi != vi_end; vi++)
		{
			if (g0_[*vi]->vertex_type == Vertex::SINK_VERTEX)
			{
				VarTable vt;
				construct_cidfg_graph(g_, g0_, *vi, vertex_map_, vt, iterator_set);
			}
			else if (g0_[*vi]->vertex_type == Vertex::ROOT_VERTEX)
			{
				RootVertex *rv = static_cast<RootVertex *>(g0_[*vi]);
				int id = g_.add_vertex(*rv);
				vertex_map_[*vi] = id;
			}
			else if (g0_[*vi]->is_hierarchical())
			{
				VarTable vt;
				construct_cidfg_graph(g_, g0_, *vi, vertex_map_, vt, iterator_set);
			}
		}

		// // DEBUG BEGIN

		// int id_root = 0;
		// for (auto &v : g_.get_vertices())
		// {
		// 	if (v->is_hierarchical())
		// 	{
		// 		HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(v);
		// 		vv->children.clear();
		// 	}
		// 	if (v->vertex_type == Vertex::ROOT_VERTEX)
		// 	{
		// 		id_root = v->id;
		// 		HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(v);
		// 		vv->children.resize(1);
		// 	}
		// }
		// for (auto &v : g_.get_vertices())
		// {
		// 	if (v->id != id_root)
		// 	{
		// 		HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(g_.get_vertex(id_root));
		// 		vv->children[0].push_back(v->id);
		// 	}
		// }
		// // DEBUG END

		Graph g1 = create_graph(g_);
		// Create a map for new id to descriptor in g1
		std::unordered_map<int, boost::graph_traits<Graph>::vertex_descriptor> vertex_id_map_2;
		for (tie(vi, vi_end) = vertices(g1); vi != vi_end; vi++)
		{
			vertex_id_map_2[g1[*vi]->id] = *vi;
		}

		// convert to undirected graph to find connected components.
		graph_traits<Graph>::edge_iterator ei, ei_end;
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> UGraph;
		UGraph ug1(num_vertices(g1));
		for (tie(ei, ei_end) = edges(g1); ei != ei_end; ++ei)
		{
			add_edge(source(*ei, g1), target(*ei, g1), ug1);
			add_edge(target(*ei, g1), source(*ei, g1), ug1);
		}

		std::vector<int> component(boost::num_vertices(ug1));
		int num_components = boost::connected_components(ug1, &component[0]);

		for (tie(vi, vi_end) = vertices(g1); vi != vi_end; vi++)
		{
			if (g1[*vi]->is_hierarchical())
			{
				HierarchicalVertex *v = static_cast<HierarchicalVertex *>(g1[*vi]);
				for (int i = 0; i < v->children.size(); i++)
				{
					set<int> children_id;
					for (int j = 0; j < v->children[i].size(); j++)
					{
						Vertex *old_vertex = g0_[vertex_id_map[v->children[i][j]]];
						Vertex *vertex = g_.get_vertex(vertex_map_[vertex_id_map[v->children[i][j]]]);
						if (old_vertex->vertex_type == Vertex::SINK_VERTEX)
						{
							boost::graph_traits<Graph>::vertex_descriptor vd = vertex_id_map_2[vertex->id];
							int component_color = component[(int)(vd)];
							for (int k = 0; k < num_vertices(g1); k++)
							{
								if (component[k] == component_color)
								{
									children_id.insert(g1[k]->id);
								}
							}
							//break;
						}
					}
					v->children[i].clear();
					for (auto &cid : children_id)
					{
						v->children[i].push_back(cid);
					}
				}
			}
		}

		return -1;
	}
	else
	{
		int id;
		Vertex *ptr = g0_[v_];
		switch (g0_[v_]->vertex_type)
		{
		case Vertex::CONST_VERTEX:
			id = g_.add_vertex(*(static_cast<ConstVertex *>(ptr)));
			break;
		case Vertex::VAR_VERTEX:
			id = g_.add_vertex(*(static_cast<VarVertex *>(ptr)));
			vt_.update_var((static_cast<VarVertex *>(ptr))->var_name, id, 0, "");
			break;
		case Vertex::REG_VAR_VERTEX:
			id = g_.add_vertex(*(static_cast<RegVarVertex *>(ptr)));
			vt_.update_var((static_cast<RegVarVertex *>(ptr))->var_name, id, 0, "");
			break;
		case Vertex::SRAM_VAR_VERTEX:
			id = g_.add_vertex(*(static_cast<SramVarVertex *>(ptr)));
			vt_.update_var((static_cast<SramVarVertex *>(ptr))->var_name, id, 0, "");
			break;
		case Vertex::INDEXING_VERTEX:
			id = g_.add_vertex(*(static_cast<IndexingVertex *>(ptr)));
			break;
		case Vertex::COMPUTATION_VERTEX:
			id = g_.add_vertex(*(static_cast<ComputationVertex *>(ptr)));
			break;
		case Vertex::READING_VERTEX:
			id = g_.add_vertex(*(static_cast<ReadingVertex *>(ptr)));
			break;
		case Vertex::WRITING_VERTEX:
			id = g_.add_vertex(*(static_cast<WritingVertex *>(ptr)));
			break;
		case Vertex::SINK_VERTEX:
			id = g_.add_vertex(*(static_cast<SinkVertex *>(ptr)));
			break;
		case Vertex::GENERAL_HIERARCHICAL_VERTEX:
			id = g_.add_vertex(*(static_cast<GeneralHierarchicalVertex *>(ptr)));
			break;
		case Vertex::BRANCH_VERTEX:
			id = g_.add_vertex(*(static_cast<BranchVertex *>(ptr)));
			break;
		case Vertex::LOOP_VERTEX:
			id = g_.add_vertex(*(static_cast<LoopVertex *>(ptr)));
			break;
		default:
			LOG(FATAL) << "Unsupported vertex type!";
			break;
		}
		vertex_map_[v_] = id;

		graph_traits<Graph>::in_edge_iterator ei, ei_end;
		for (tie(ei, ei_end) = in_edges(v_, g0_); ei != ei_end; ei++)
		{
			if (g0_[*ei].flag_unsimplified)
			{
				int vid;
				if (vertex_map_.find(source(*ei, g0_)) != vertex_map_.end())
				{
					vid = vertex_map_[source(*ei, g0_)];
				}
				else
				{
					vid = construct_cidfg_graph(g_, g0_, source(*ei, g0_), vertex_map_, vt_, iterator_set_);
				}
				Edge e(vid, g0_[*ei].src_port, id, g0_[*ei].dest_port, g0_[*ei].edge.var_name, g0_[*ei].edge.edge_type);
				g_.add_edge(e);
			}
			else
			{
				int vid = construct_cidfg_graph_branch(g_, g0_[*ei], vt_, iterator_set_);
				Edge e(vid, g0_[*ei].src_port, id, g0_[*ei].dest_port, g0_[*ei].edge.var_name, g0_[*ei].edge.edge_type);
				g_.add_edge(e);
			}
		}
		return id;
	}
	return -1;
}

int BranchSimplifier::construct_cidfg_graph_branch(CidfgGraph &g_, EdgeProperty vr_, VarTable &vt_, std::unordered_map<string, int> iterator_set_)
{
	int id = -1;
	IntPolynomialTable ipt = vr_.ipt;

	if (ipt.is_zero())
	{
		ConstVertex v;
		v.set_int_value(0);
		id = g_.add_vertex(v);
	}
	else if (ipt.is_constant())
	{
		ConstVertex v;
		v.set_int_value(ipt.get_bias());
		id = g_.add_vertex(v);
	}
	else
	{
		int id2 = -1;
		int j = 0;
		for (auto &term : ipt.get_table())
		{
			multiset<string> vars = term.first;
			int factor = term.second;
			if (term.first.empty())
			{
				ConstVertex v;
				v.set_int_value(factor);
				id2 = g_.add_vertex(v);
			}
			else
			{
				int i = 0;
				for (auto &token : vars)
				{
					int const_id;
					int const_port;
					if (vt_.exist(token))
					{
						const_id = vt_.get_vertex_id(token);
						const_port = vt_.get_vertex_port(token);
					}
					else
					{
						VarVertex v;
						v.var_name = token;
						if (iterator_set_.find(token) != iterator_set_.end())
						{
							v.is_iterator = true;
							v.loop_id = iterator_set_[token];
						}
						const_id = g_.add_vertex(v);
						const_port = 0;
						vt_.update_var(token, const_id, const_port, "");
					}
					int last_id = id2;
					if (i != 0)
					{
						ComputationVertex v1;
						v1.func_name = "*";
						int compute_id = g_.add_vertex(v1);
						Edge e0(last_id, 0, compute_id, 0);
						Edge e1(const_id, const_port, compute_id, 1);
						g_.add_edge(e0);
						g_.add_edge(e1);
						id2 = compute_id;
					}
					else
					{
						id2 = const_id;
					}
					i++;
				}
				if (factor != 1)
				{
					ComputationVertex v0;
					v0.func_name = "*";
					int compute_id = g_.add_vertex(v0);
					ConstVertex v1;
					v1.set_int_value(factor);
					int const_id = g_.add_vertex(v1);
					Edge e0(id2, 0, compute_id, 0);
					Edge e1(const_id, 0, compute_id, 1);
					g_.add_edge(e0);
					g_.add_edge(e1);
					id2 = compute_id;
				}
			}

			if (j != 0)
			{
				ComputationVertex v0;
				v0.func_name = "+";
				int compute_id = g_.add_vertex(v0);
				Edge e0(id, 0, compute_id, 0);
				Edge e1(id2, 0, compute_id, 1);
				g_.add_edge(e0);
				g_.add_edge(e1);
				id = compute_id;
			}
			else
			{
				id = id2;
			}
			j++;
		}
	}
	return id;
}

EdgeProperty BranchSimplifier::cal_var_record(Graph &g_, boost::graph_traits<Graph>::vertex_descriptor v_)
{
	switch (g_[v_]->vertex_type)
	{
	case Vertex::VAR_VERTEX:
	{
		graph_traits<Graph>::out_edge_iterator ei, ei_end;
		EdgeProperty vr;
		for (tie(ei, ei_end) = out_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				IntPolynomialTable ipt({{{static_cast<VarVertex *>(g_[v_])->var_name}, 1}});
				g_[*ei].ipt = ipt;
				vr.ipt = ipt;
				g_[*ei].flag_set = true;
				g_[*ei].flag_unsimplified = false;
			}
		}
		return vr;
		break;
	}
	case Vertex::REG_VAR_VERTEX:
	{
		graph_traits<Graph>::out_edge_iterator ei, ei_end;
		EdgeProperty vr;
		for (tie(ei, ei_end) = out_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				IntPolynomialTable ipt({{{static_cast<RegVarVertex *>(g_[v_])->var_name}, 1}});
				g_[*ei].ipt = ipt;
				vr.ipt = ipt;
				g_[*ei].flag_set = true;
				g_[*ei].flag_unsimplified = true;
			}
		}
		return vr;
		break;
	}
	case Vertex::SRAM_VAR_VERTEX:
	{
		graph_traits<Graph>::out_edge_iterator ei, ei_end;
		EdgeProperty vr;
		for (tie(ei, ei_end) = out_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				IntPolynomialTable ipt({{{static_cast<SramVarVertex *>(g_[v_])->var_name}, 1}});
				g_[*ei].ipt = ipt;
				vr.ipt = ipt;
				g_[*ei].flag_set = true;
				g_[*ei].flag_unsimplified = true;
			}
		}
		return vr;
		break;
	}
	case Vertex::CONST_VERTEX:
	{
		graph_traits<Graph>::out_edge_iterator ei, ei_end;
		EdgeProperty vr;
		for (tie(ei, ei_end) = out_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				multiset<string> s;
				IntPolynomialTable ipt({{s, (static_cast<ConstVertex *>(g_[v_]))->int_data}});
				g_[*ei].ipt = ipt;
				vr.ipt = ipt;
				g_[*ei].flag_set = true;
				g_[*ei].flag_unsimplified = false;
			}
		}
		return vr;
		break;
	}
	case Vertex::SINK_VERTEX:
	{
		graph_traits<Graph>::in_edge_iterator ei, ei_end;
		EdgeProperty vr;
		for (tie(ei, ei_end) = in_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				vr = cal_var_record(g_, source(*ei, g_));
			}
		}
		return vr;
		break;
	}
	case Vertex::GENERAL_HIERARCHICAL_VERTEX:
	case Vertex::BRANCH_VERTEX:
	case Vertex::LOOP_VERTEX:
	{
		graph_traits<Graph>::in_edge_iterator ei, ei_end;

		for (tie(ei, ei_end) = in_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				cal_var_record(g_, source(*ei, g_));
			}
		}
		graph_traits<Graph>::out_edge_iterator oei, oei_end;
		for (tie(oei, oei_end) = out_edges(v_, g_); oei != oei_end; oei++)
		{
			if (!(g_[*oei].flag_set))
			{
				g_[*oei].flag_set = true;
				g_[*oei].flag_unsimplified = true;
			}
		}
		EdgeProperty vr;
		return vr;
		break;
	}
	case Vertex::COMPUTATION_VERTEX:
	{
		bool flag_unsimplified = false;
		std::unordered_map<int, EdgeProperty> map_vr;
		graph_traits<Graph>::in_edge_iterator ei, ei_end;
		for (tie(ei, ei_end) = in_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				cal_var_record(g_, source(*ei, g_));
			}
			map_vr[g_[*ei].dest_port] = g_[*ei];
			if (g_[*ei].flag_unsimplified)
			{
				flag_unsimplified = true;
			}
		}
		ComputationVertex *cv = static_cast<ComputationVertex *>(g_[v_]);
		if (cv->func_name == "ld")
		{
			flag_unsimplified = true;
		}

		EdgeProperty vr;
		if (flag_unsimplified == false)
		{
			ComputationVertex *cv = static_cast<ComputationVertex *>(g_[v_]);

			if (cv->func_name == "+" || cv->func_name == "add")
			{
				vr.ipt.add(map_vr[0].ipt);
				vr.ipt.add(map_vr[1].ipt);
			}
			else if (cv->func_name == "-" || cv->func_name == "sub")
			{
				vr.ipt.add(map_vr[0].ipt);
				vr.ipt.sub(map_vr[1].ipt);
			}
			else if (cv->func_name == "*" || cv->func_name == "mul")
			{
				vr.ipt.add(map_vr[0].ipt);
				vr.ipt.mul(map_vr[1].ipt);
			}
			else if (cv->func_name == "/" || cv->func_name == "div")
			{
				vr.ipt.add(map_vr[0].ipt);
				vr.ipt.div_const(map_vr[1].ipt);
			}
			else if (cv->func_name == "=" || cv->func_name == "assign")
			{
				vr.ipt.add(map_vr[0].ipt);
			}
			else
			{
				LOG(FATAL) << "Unsupported computation nodes [" << cv->func_name << "]";
			}

			graph_traits<Graph>::out_edge_iterator oei, oei_end;
			for (tie(oei, oei_end) = out_edges(v_, g_); oei != oei_end; oei++)
			{
				g_[*oei].ipt = vr.ipt;
				g_[*oei].flag_set = true;
			}
		}
		else
		{
			graph_traits<Graph>::out_edge_iterator oei, oei_end;
			for (tie(oei, oei_end) = out_edges(v_, g_); oei != oei_end; oei++)
			{
				g_[*oei].ipt = vr.ipt;
				g_[*oei].flag_set = true;
				g_[*oei].flag_unsimplified = true;
			}
		}
		return vr;
		break;
	}
	default:
	{
		std::unordered_map<int, EdgeProperty> map_vr;
		graph_traits<Graph>::in_edge_iterator ei, ei_end;
		for (tie(ei, ei_end) = in_edges(v_, g_); ei != ei_end; ei++)
		{
			if (!(g_[*ei].flag_set))
			{
				cal_var_record(g_, source(*ei, g_));
			}
		}

		EdgeProperty vr;
		graph_traits<Graph>::out_edge_iterator oei, oei_end;
		for (tie(oei, oei_end) = out_edges(v_, g_); oei != oei_end; oei++)
		{
			g_[*oei].ipt = vr.ipt;
			g_[*oei].flag_set = true;
			g_[*oei].flag_unsimplified = true;
		}
		return vr;
		break;
	}
	}

	EdgeProperty vr;
	return vr;
}
} // namespace cidfg
} // namespace vesyla