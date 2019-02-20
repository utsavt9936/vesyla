// Copyright (C) 2019 Yu Yang
// 
// This file is part of Vesyla.
// 
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

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