#ifndef __VESYLA_CODEGEN_OPTIMIZER_HPP__
#define __VESYLA_CODEGEN_OPTIMIZER_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"
#include "schedule/Descriptor.hpp"
#include "IteratorReplacementEngine.hpp"
#include "MulDivTransEngine.hpp"
#include "ComputationVertexConverter.hpp"
#include "LoopVertexConverter.hpp"
#include "GeneralHierarchicalVertexConverter.hpp"
#include "BranchVertexConverter.hpp"
#include "IndexVertexConverter.hpp"
#include "RouteEngine.hpp"
#include "RootVertexConverter.hpp"
#include "SwbRearrangeEngine.hpp"
#include "CleanConverter.hpp"
#include "DescriptorGenerator.hpp"
#include "cidfg/ScriptGenerator.hpp"

namespace vesyla
{
namespace codegen
{
class Optimizer
{
public:
	Optimizer();
	~Optimizer();
	schedule::Descriptor optimize(cidfg::CidfgGraph &g_);

private:
	void to_dot_graph(cidfg::CidfgGraph &g_, int stage_);
	void to_dot_graph(schedule::Descriptor &d_, int stage_);
	void gen_script();
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_FEOPT_OPTIMIZER_HPP__