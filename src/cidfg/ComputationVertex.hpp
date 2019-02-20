#ifndef __VESYLA_CIDFG_COMPUTATION_VERTEX_HPP__
#define __VESYLA_CIDFG_COMPUTATION_VERTEX_HPP__

#include "FunctionVertex.hpp"
#include "IntPolynomialTable.hpp"

namespace vesyla
{
namespace cidfg
{
class ComputationVertex : public FunctionVertex
{
public:
  string func_name;
  bool is_on_dpu;
  bool is_polynomial_func;
  IntPolynomialTable ipt;

public:
  ComputationVertex();
  ~ComputationVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_COMPUTATION_VERTEX_HPP__
