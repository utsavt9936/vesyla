#ifndef __VESYLA_FEOPT_ENGINE_HPP__
#define __VESYLA_FEOPT_ENGINE_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"

namespace vesyla
{
namespace feopt
{
class Engine
{
public:
	Engine();
	virtual ~Engine() = 0;
	virtual void transform(cidfg::CidfgGraph &g_) = 0;
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_ENGINE_HPP__