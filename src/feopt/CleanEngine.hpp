#ifndef __VESYLA_FEOPT_CLEAN_ENGINE_HPP__
#define __VESYLA_FEOPT_CLEAN_ENGINE_HPP__

#include "Engine.hpp"
//#include <boost/graph/graph_traits.hpp>
//#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/transitive_closure.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

namespace vesyla
{
namespace feopt
{
class CleanEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_CLEAN_ENGINE_HPP__