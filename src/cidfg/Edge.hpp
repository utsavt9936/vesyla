#ifndef __VESYLA_CIDFG_EDGE_HPP__
#define __VESYLA_CIDFG_EDGE_HPP__

#include "Object.hpp"

namespace vesyla
{
namespace cidfg
{
class Edge : public Object
{
public:
  enum EdgeType
  {
    SCALAR_DATA_SIG,
    VECTOR_DATA_SIG,
    SRAM_VECTOR_DATA_SIG,
    SCALAR_CONTROL_SIG,
    DEPENDENCY
  };

public:
  int src_id;
  int src_port;
  int dest_id;
  int dest_port;
  string var_name;
  EdgeType edge_type;
  int d_lo;
  int d_hi;
  static int temp_name_counter;

public:
  Edge();
  Edge(int src_id_, int src_port_, int dest_id_, int dest_port_, string var_name_ = "", EdgeType edge_type_ = SCALAR_DATA_SIG, int d_lo_ = 1, int d_hi_ = INT_MAX);
  ~Edge();

  bool is_weak_dependency();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_EDGE_HPP__