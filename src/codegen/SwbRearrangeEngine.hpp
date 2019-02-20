#ifndef __VESYLA_CODEGEN_SWB_REARRANGE_ENGINE_HPP__
#define __VESYLA_CODEGEN_SWB_REARRANGE_ENGINE_HPP__

#include "Engine.hpp"

namespace vesyla
{
namespace codegen
{
class SwbRearrangeEngine : public Engine
{
public:
  void transform(cidfg::CidfgGraph &g_);

private:
  void find_all_swb_in_hierarchical_vetex(cidfg::CidfgGraph &g_, int v_, vector<int> &swb_instr_vertices_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_SWB_REARRANGE_ENGINE_HPP__