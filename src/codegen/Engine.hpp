#ifndef __VESYLA_CODEGEN_ENGINE_HPP__
#define __VESYLA_CODEGEN_ENGINE_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"

namespace vesyla
{
namespace codegen
{

class Engine
{
public:
  Engine();
  ~Engine();
  virtual void transform(cidfg::CidfgGraph &g_) = 0;
};

} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_ENGINE_HPP__