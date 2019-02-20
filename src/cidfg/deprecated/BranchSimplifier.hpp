#ifndef __VESYLA_CIDFG_BRANCH_SIMPLIFIER_HPP__
#define __VESYLA_CIDFG_BRANCH_SIMPLIFIER_HPP__

#include "CidfgGraph.hpp"
#include "IntPolynomialTable.hpp"
#include "VarTable.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>

namespace vesyla
{
namespace cidfg
{
class EdgeProperty
{
public:
	IntPolynomialTable ipt;
	int src_port;
	int dest_port;
	bool flag_set;
	bool flag_unsimplified;
	Edge edge;

public:
	EdgeProperty() : flag_set(false), flag_unsimplified(false), edge(), ipt() {}
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, Vertex *, EdgeProperty> Graph;

class BranchSimplifier
{
public:
	BranchSimplifier();
	~BranchSimplifier();

public:
	void simplify(CidfgGraph &new_g_, CidfgGraph &g_);

public:
	Graph create_graph(CidfgGraph &g_);
	EdgeProperty cal_var_record(Graph &g_, boost::graph_traits<Graph>::vertex_descriptor v_);
	int construct_cidfg_graph_branch(CidfgGraph &g_, EdgeProperty vr_, VarTable &vt_, std::unordered_map<string, int> iterator_set_);
	int construct_cidfg_graph(CidfgGraph &g_, Graph &g0_, boost::graph_traits<Graph>::vertex_descriptor v_, std::unordered_map<boost::graph_traits<Graph>::vertex_descriptor, int> &vertex_map_, VarTable &vt_, std::unordered_map<string, int> iterator_set_ = {{}});
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_BRANCH_SIMPLIFIER_HPP__