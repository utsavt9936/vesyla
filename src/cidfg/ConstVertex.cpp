#include "ConstVertex.hpp"

namespace vesyla
{
namespace cidfg
{
ConstVertex::ConstVertex()
{
  vertex_type = CONST_VERTEX;
}
ConstVertex::~ConstVertex()
{
}
void ConstVertex::set_int_value(int v_)
{
  int_data = v_;
  value_type = INT;
}
void ConstVertex::set_float_value(float v_)
{
  float_data = v_;
  value_type = FLOAT;
}
} // namespace cidfg
} // namespace vesyla