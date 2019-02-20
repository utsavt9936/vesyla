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