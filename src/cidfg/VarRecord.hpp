#ifndef __VESYLA_CIDFG_VAR_RECORD_HPP__
#define __VESYLA_CIDFG_VAR_RECORD_HPP__

#include "util/Common.hpp"
#include "Edge.hpp"
#include "VIR/Coordinate.hpp"
#include <set>

namespace vesyla
{
namespace cidfg
{
class VarRecord
{
public:
  int bind_vertex_id;
  int bind_vertex_port;
  string domain_signature;
  Edge::EdgeType edge_type;
  VIR::Coordinate coord;
  bool isfixed;
  std::set<int> referenced_by;
  int start_vertex_id;
  int size_vertex_id;

public:
  VarRecord();
  ~VarRecord();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_VAR_RECORD_HPP__