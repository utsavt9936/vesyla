#include "Edge.hpp"

namespace vesyla
{
namespace cidfg
{
int Edge::temp_name_counter = 0;
Edge::Edge() : edge_type(SCALAR_DATA_SIG), d_lo(1), d_hi(INT_MAX)
{
  var_name = "temp_var_" + to_string(temp_name_counter);
  temp_name_counter++;
}
Edge::Edge(int src_id_, int src_port_, int dest_id_, int dest_port_, string var_name_, EdgeType edge_type_, int d_lo_, int d_hi_) : src_id(src_id_), src_port(src_port_), dest_id(dest_id_), dest_port(dest_port_), edge_type(edge_type_), d_lo(d_lo_), d_hi(d_hi_)
{
  if (var_name_ == "")
  {
    var_name = "temp_var_" + to_string(temp_name_counter);
    temp_name_counter++;
  }
  else
  {
    var_name = var_name_;
  }
}
Edge::~Edge()
{
}

bool Edge::is_weak_dependency()
{
  if (edge_type != DEPENDENCY)
  {
    return false;
  }

  string ending = "_weak";
  if (var_name.length() >= ending.length())
  {
    return (0 == var_name.compare(var_name.length() - ending.length(), ending.length(), ending));
  }
  else
  {
    return false;
  }
}
} // namespace cidfg
} // namespace vesyla