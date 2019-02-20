#ifndef __VESYLA_CODEGEN_ROUTE_ENGINE_HPP__
#define __VESYLA_CODEGEN_ROUTE_ENGINE_HPP__

#include "Engine.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "VManager/MemoryManager.hpp"

namespace vesyla
{
namespace codegen
{
class RouteEngine : public Engine
{
public:
  void transform(cidfg::CidfgGraph &g_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_ROUTE_ENGINE_HPP__