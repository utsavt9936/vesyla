#ifndef __VESYLA_FEOPT_OPTIMIZER_HPP__
#define __VESYLA_FEOPT_OPTIMIZER_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"
#include "ExprSimpEngine.hpp"
#include "SrcConvEngine.hpp"
#include "RwiMergeEngine.hpp"
#include "BindEngine.hpp"
#include "DependencyAnalyzeEngine.hpp"
#include "CleanEngine.hpp"
#include "cidfg/ScriptGenerator.hpp"

namespace vesyla
{
namespace feopt
{
class Optimizer
{
public:
	Optimizer();
	~Optimizer();
	void optimize(cidfg::CidfgGraph &g_);

private:
	void to_dot_graph(cidfg::CidfgGraph &g_, int stage_);
	void gen_script();
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_OPTIMIZER_HPP__