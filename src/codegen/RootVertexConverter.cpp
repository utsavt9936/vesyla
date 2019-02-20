#include "RootVertexConverter.hpp"

namespace vesyla
{
namespace codegen
{
RootVertexConverter::RootVertexConverter()
{
}
RootVertexConverter::~RootVertexConverter()
{
}
void RootVertexConverter::convert(cidfg::CidfgGraph &g_)
{
  std::set<int> remove_vertices;
  for (auto &v : g_.get_vertices())
  {
    if (v->vertex_type == cidfg::Vertex::ROOT_VERTEX)
    {
      cidfg::HierarchicalVertex *vv = static_cast<cidfg::HierarchicalVertex *>(v);

      if (vv->children.size() == 0)
      {
        remove_vertices.insert(vv->id);
      }
    }
  }
  for (auto &id : remove_vertices)
  {
    g_.del_vertex(id);
  }
}
} // namespace codegen
} // namespace vesyla