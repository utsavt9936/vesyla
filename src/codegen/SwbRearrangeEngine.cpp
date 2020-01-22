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

#include "SwbRearrangeEngine.hpp"

using namespace vesyla::cidfg;

namespace vesyla
{
namespace codegen
{

std::set<string> find_path(VIR::Coordinate src_coord, VIR::Coordinate dest_coord)
{
  if (src_coord.row > dest_coord.row)
  {
    VIR::Coordinate temp_coord = src_coord;
    src_coord = dest_coord;
    dest_coord = temp_coord;
  }
  std::set<string> occupied_sram_cells;
  for (int i = src_coord.row; i <= dest_coord.row; i++)
  {
    VIR::Coordinate c(i, src_coord.column);
    occupied_sram_cells.insert("SRAM_CELL_" + c.to_str());
  }
  int big_col = src_coord.column > dest_coord.column ? src_coord.column : dest_coord.column;
  int small_col = src_coord.column <= dest_coord.column ? src_coord.column : dest_coord.column;
  for (int i = small_col; i <= big_col; i++)
  {
    VIR::Coordinate c(dest_coord.row, i);
    occupied_sram_cells.insert("SRAM_CELL_" + c.to_str());
  }
  return occupied_sram_cells;
}

void SwbRearrangeEngine::find_all_swb_in_hierarchical_vetex(cidfg::CidfgGraph &g_, int v_, vector<int> &swb_instr_vertices_)
{
  HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(g_.get_vertex(v_));
  for (int i = 0; i < vv->children.size(); i++)
  {
    for (int j = 0; j < vv->children[i].size(); j++)
    {
      if (g_.get_vertex(vv->children[i][j])->vertex_type == Vertex::SWB_INSTR_VERTEX)
      {
        swb_instr_vertices_.push_back(vv->children[i][j]);
      }
      else if (g_.get_vertex(vv->children[i][j])->is_hierarchical())
      {
        find_all_swb_in_hierarchical_vetex(g_, vv->children[i][j], swb_instr_vertices_);
      }
    }
  }
}
void SwbRearrangeEngine::find_all_route_in_hierarchical_vetex(cidfg::CidfgGraph &g_, int v_, vector<int> &route_instr_vertices_)
{
  HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(g_.get_vertex(v_));
  for (int i = 0; i < vv->children.size(); i++)
  {
    for (int j = 0; j < vv->children[i].size(); j++)
    {
      if (g_.get_vertex(vv->children[i][j])->vertex_type == Vertex::ROUTE_INSTR_VERTEX)
      {
        route_instr_vertices_.push_back(vv->children[i][j]);
      }
      else if (g_.get_vertex(vv->children[i][j])->is_hierarchical())
      {
        find_all_swb_in_hierarchical_vetex(g_, vv->children[i][j], route_instr_vertices_);
      }
    }
  }
}
void SwbRearrangeEngine::transform(cidfg::CidfgGraph &g_)
{
  rearrange_swb(g_);
  merge_swb(g_);

  // IMPORTANT NOTE：
  // DUE TO BUG IN DIMARCH, DIMARCH AGU CAN BE CONFIGURED ONLY AFTER A ROUTING INSTRUCTION. IF WE MOVE
  // ROUTING INSTRUCTION OUTSIDE LOOP AND MERGE THEM, SOME AGU INSTRUCTION WILL
  // NOT BE ACTIVE DUE TO LACK OF ROUTING INSTRUCTION.
  rearrange_route(g_);
  merge_route(g_);
}

void SwbRearrangeEngine::rearrange_route(cidfg::CidfgGraph &g_)
{
  bool flag_changed = true;
  while (flag_changed)
  {
    flag_changed = false;
    for (auto &v : g_.get_vertices())
    {
      if (v->vertex_type == Vertex::ROOT_VERTEX)
      {
        continue;
      }
      if (v->is_hierarchical())
      {
        std::vector<int> swb_instr_vertices;
        std::vector<int> all_swb_instr_vertices;
        HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(v);
        if (vv->children.size() >= 2)
        {
          continue;
        }
        for (int i = 0; i < vv->children.size(); i++)
        {
          for (int j = 0; j < vv->children[i].size(); j++)
          {
            if (g_.get_vertex(vv->children[i][j])->vertex_type == Vertex::ROUTE_INSTR_VERTEX)
            {
              swb_instr_vertices.push_back(vv->children[i][j]);
            }
          }
        }
        find_all_route_in_hierarchical_vetex(g_, v->id, all_swb_instr_vertices);
        for (int i = 0; i < swb_instr_vertices.size(); i++)
        {
          if (swb_instr_vertices[i] < 0)
          {
            continue;
          }
          RouteInstrVertex *v0 = static_cast<RouteInstrVertex *>(g_.get_vertex(swb_instr_vertices[i]));
          BIR::RouteInstruction *instr0 = static_cast<BIR::RouteInstruction *>(v0->instr);
          std::set<string> str0 = find_path(instr0->sourceCoordinate, instr0->destCoordinate);
          for (int j = 0; j < all_swb_instr_vertices.size(); j++)
          {
            if (all_swb_instr_vertices[j] < 0)
            {
              continue;
            }
            if (all_swb_instr_vertices[j] == swb_instr_vertices[i])
            {
              continue;
            }
            RouteInstrVertex *v1 = static_cast<RouteInstrVertex *>(g_.get_vertex(all_swb_instr_vertices[j]));
            BIR::RouteInstruction *instr1 = static_cast<BIR::RouteInstruction *>(v1->instr);
            std::set<string> str1 = find_path(instr1->sourceCoordinate, instr1->destCoordinate);
            bool flag_conflict = false;
            for (auto &s : str0)
            {
              if (str1.find(s) != str1.end())
              {
                flag_conflict = true;
                break;
              }
            }
            if (flag_conflict)
            {
              if (!(instr0->sourceCoordinate.to_str() == instr1->sourceCoordinate.to_str() && instr0->destCoordinate.to_str() == instr1->destCoordinate.to_str()) && !(instr0->sourceCoordinate.to_str() == instr1->destCoordinate.to_str() && instr0->destCoordinate.to_str() == instr1->sourceCoordinate.to_str()))
              {
                all_swb_instr_vertices[j] = -1;
                swb_instr_vertices[i] = -1;
                break;
              }
            }
          }
        }

        int curr_parent_id;
        int curr_child_index;
        g_.get_parent(v->id, curr_parent_id, curr_child_index);
        HierarchicalVertex *parent_vertex = static_cast<HierarchicalVertex *>(g_.get_vertex(curr_parent_id));
        if (curr_parent_id >= 0 && curr_child_index >= 0)
        {
          for (int i = 0; i < swb_instr_vertices.size(); i++)
          {
            if (swb_instr_vertices[i] < 0)
            {
              continue;
            }

            int id = swb_instr_vertices[i];
            int parent_id;
            int child_index;
            g_.get_parent(id, parent_id, child_index);
            if (parent_id >= 0 && child_index >= 0)
            {
              HierarchicalVertex *vertex = static_cast<HierarchicalVertex *>(g_.get_vertex(parent_id));
              vector<int> vec = vertex->children[child_index];
              vertex->children[child_index].clear();
              for (auto &c : vec)
              {
                if (c == id)
                {
                  continue;
                }
                vertex->children[child_index].push_back(c);
              }
            }
            flag_changed = true;
            parent_vertex->add_child(curr_child_index, id);

            // change the outgoing dependency edge point to the hierarchical vertex
            for (auto &e0 : g_.get_edges())
            {
              if (e0->edge_type == cidfg::Edge::DEPENDENCY && e0->src_id == id)
              {
                e0->dest_id = parent_id;
              }
            }
          }
        }
      }
    }
  }
}

void SwbRearrangeEngine::rearrange_swb(cidfg::CidfgGraph &g_)
{
  bool flag_changed = true;
  while (flag_changed)
  {
    flag_changed = false;
    for (auto &v : g_.get_vertices())
    {
      if (v->vertex_type == Vertex::ROOT_VERTEX || v->vertex_type == Vertex::BRANCH_VERTEX)
      {
        continue;
      }
      if (v->is_hierarchical())
      {
        std::vector<int> swb_instr_vertices;
        std::vector<int> all_swb_instr_vertices;
        HierarchicalVertex *vv = static_cast<HierarchicalVertex *>(v);
        if (vv->children.size() >= 2)
        {
          continue;
        }
        for (int i = 0; i < vv->children.size(); i++)
        {
          for (int j = 0; j < vv->children[i].size(); j++)
          {
            if (g_.get_vertex(vv->children[i][j])->vertex_type == Vertex::SWB_INSTR_VERTEX)
            {
              swb_instr_vertices.push_back(vv->children[i][j]);
            }
          }
        }
        find_all_swb_in_hierarchical_vetex(g_, v->id, all_swb_instr_vertices);
        for (int i = 0; i < swb_instr_vertices.size(); i++)
        {
          if (swb_instr_vertices[i] < 0)
          {
            continue;
          }
          SwbInstrVertex *v0 = static_cast<SwbInstrVertex *>(g_.get_vertex(swb_instr_vertices[i]));
          BIR::SWBInstruction *instr0 = static_cast<BIR::SWBInstruction *>(v0->instr);
          string str0 = instr0->destination.to_string();
          for (int j = 0; j < all_swb_instr_vertices.size(); j++)
          {
            if (all_swb_instr_vertices[j] < 0)
            {
              continue;
            }
            if (all_swb_instr_vertices[j] == swb_instr_vertices[i])
            {
              continue;
            }
            SwbInstrVertex *v1 = static_cast<SwbInstrVertex *>(g_.get_vertex(all_swb_instr_vertices[j]));
            BIR::SWBInstruction *instr1 = static_cast<BIR::SWBInstruction *>(v1->instr);
            string str1 = instr1->destination.to_string();
            if (str0 == str1 && instr0->source.to_string() != instr1->source.to_string())
            {
              all_swb_instr_vertices[j] = -1;
              swb_instr_vertices[i] = -1;
              break;
            }
          }
        }

        int curr_parent_id;
        int curr_child_index;
        g_.get_parent(v->id, curr_parent_id, curr_child_index);
        HierarchicalVertex *parent_vertex = static_cast<HierarchicalVertex *>(g_.get_vertex(curr_parent_id));
        if (curr_parent_id >= 0 && curr_child_index >= 0)
        {
          for (int i = 0; i < swb_instr_vertices.size(); i++)
          {
            if (swb_instr_vertices[i] < 0)
            {
              continue;
            }

            int id = swb_instr_vertices[i];
            int parent_id;
            int child_index;
            g_.get_parent(id, parent_id, child_index);
            if (parent_id >= 0 && child_index >= 0)
            {
              HierarchicalVertex *vertex = static_cast<HierarchicalVertex *>(g_.get_vertex(parent_id));
              vector<int> vec = vertex->children[child_index];
              vertex->children[child_index].clear();
              for (auto &c : vec)
              {
                if (c == id)
                {
                  continue;
                }
                vertex->children[child_index].push_back(c);
              }
            }
            flag_changed = true;
            parent_vertex->add_child(curr_child_index, id);

            // change the outgoing dependency edge point to the hierarchical vertex
            for (auto &e0 : g_.get_edges())
            {
              if (e0->edge_type == cidfg::Edge::DEPENDENCY && e0->src_id == id)
              {
                e0->dest_id = parent_id;
              }
            }
          }
        }
      }
    }
  }
}

void SwbRearrangeEngine::merge_swb(cidfg::CidfgGraph &g_)
{
  std::set<int> remove_vertices;

  for (auto &e0 : g_.get_edges())
  {
    for (auto &e1 : g_.get_edges())
    {
      if (e0->src_id != e1->src_id && e0->dest_id == e1->dest_id && e0->dest_port == e1->dest_port && e0->src_port == e1->src_port)
      {
        if (g_.get_vertex(e0->src_id)->vertex_type == Vertex::SWB_INSTR_VERTEX && g_.get_vertex(e1->src_id)->vertex_type == Vertex::SWB_INSTR_VERTEX)
        {
          SwbInstrVertex *v0 = static_cast<SwbInstrVertex *>(g_.get_vertex(e0->src_id));
          SwbInstrVertex *v1 = static_cast<SwbInstrVertex *>(g_.get_vertex(e1->src_id));
          if (remove_vertices.find(v0->id) != remove_vertices.end())
          {
            continue;
          }
          BIR::SWBInstruction *instr0 = static_cast<BIR::SWBInstruction *>(v0->instr);
          BIR::SWBInstruction *instr1 = static_cast<BIR::SWBInstruction *>(v1->instr);
          if (instr0->source.to_string() == instr1->source.to_string() && instr0->destination.to_string() == instr1->destination.to_string())
          {
            remove_vertices.insert(v1->id);
          }
        }
      }
    }
  }

  for (auto id : remove_vertices)
  {
    g_.del_vertex(id);
  }
}

void SwbRearrangeEngine::merge_route(cidfg::CidfgGraph &g_)
{
  std::set<int> remove_vertices;

  for (auto &e0 : g_.get_edges())
  {
    for (auto &e1 : g_.get_edges())
    {
      if (e0->src_id != e1->src_id && e0->dest_id == e1->dest_id && e0->dest_port == e1->dest_port && e0->src_port == e1->src_port)
      {
        if (g_.get_vertex(e0->src_id)->vertex_type == Vertex::ROUTE_INSTR_VERTEX && g_.get_vertex(e1->src_id)->vertex_type == Vertex::ROUTE_INSTR_VERTEX)
        {
          RouteInstrVertex *v0 = static_cast<RouteInstrVertex *>(g_.get_vertex(e0->src_id));
          RouteInstrVertex *v1 = static_cast<RouteInstrVertex *>(g_.get_vertex(e1->src_id));
          if (remove_vertices.find(v0->id) != remove_vertices.end())
          {
            continue;
          }
          BIR::RouteInstruction *instr0 = static_cast<BIR::RouteInstruction *>(v0->instr);
          BIR::RouteInstruction *instr1 = static_cast<BIR::RouteInstruction *>(v1->instr);
          if ((instr0->sourceCoordinate.to_str() == instr1->sourceCoordinate.to_str() && instr0->destCoordinate.to_str() == instr1->destCoordinate.to_str()) || (instr0->sourceCoordinate.to_str() == instr1->destCoordinate.to_str() && instr0->destCoordinate.to_str() == instr1->sourceCoordinate.to_str()))
          {
            remove_vertices.insert(v1->id);
          }
        }
      }
    }
  }

  for (auto id : remove_vertices)
  {
    g_.del_vertex(id);
  }
}

} // namespace codegen
} // namespace vesyla