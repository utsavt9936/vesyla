#include "ComputationVertex.hpp"

namespace vesyla
{
namespace cidfg
{
ComputationVertex::ComputationVertex()
{
  vertex_type = COMPUTATION_VERTEX;
  is_on_dpu = false;
  is_polynomial_func = false;
}
ComputationVertex::~ComputationVertex()
{
}
} // namespace cidfg
} // namespace vesyla