#ifndef __VESYLA_FEOPT_EXPR_SIMP_ENGINE_HPP__
#define __VESYLA_FEOPT_EXPR_SIMP_ENGINE_HPP__

#include "Engine.hpp"
#include "cidfg/IntPolynomialTable.hpp"
#include "cidfg/VarTable.hpp"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>

namespace vesyla
{
namespace feopt
{
class EdgeProperty
{
public:
	cidfg::IntPolynomialTable ipt;
	int src_port;
	int dest_port;
	bool flag_set;
	bool flag_unsimplified;
	cidfg::Edge edge;

public:
	EdgeProperty() : flag_set(false), flag_unsimplified(false), edge(), ipt() {}
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, cidfg::Vertex *, EdgeProperty> Graph;

class ExprSimpEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);

private:
	int _var_counter;
	std::vector<cidfg::Edge> _dependency_edges;

private:
	string get_random_temp_var_name();
	bool simplify(cidfg::CidfgGraph &g_, cidfg::VarTable &t_);
	void rebuild(cidfg::CidfgGraph &g_, cidfg::VarTable &t_);
	Graph create_graph(cidfg::CidfgGraph &g_);
	EdgeProperty cal_var_record(Graph &g_, boost::graph_traits<Graph>::vertex_descriptor v_);
	void find_source_vertices(Graph &g0_, boost::graph_traits<Graph>::edge_descriptor e0_, cidfg::VarTable &vt_);
	int construct_cidfg_graph_branch(cidfg::CidfgGraph &g_, EdgeProperty vr_, cidfg::VarTable &vt_, int parent_id_, int child_index_);
	void record_needed_vertices(boost::graph_traits<Graph>::vertex_descriptor v_, Graph &g0_, set<int> &needed_vertices_);
	void transfer_dependency_edges(cidfg::CidfgGraph &g_, int old_branch_id_, int new_branch_id_);
	void find_and_remove_dependency_edges(cidfg::CidfgGraph &g_);
	void add_dependency_edges(cidfg::CidfgGraph &g_);
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_EXPR_SIMP_ENGINE_HPP__