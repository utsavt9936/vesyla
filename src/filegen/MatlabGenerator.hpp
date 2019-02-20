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

#ifndef __VESYLA_FILEGEN_MATLAB_GENERATOR_HPP__
#define __VESYLA_FILEGEN_MATLAB_GENERATOR_HPP__

#include <boost/algorithm/string.hpp>
#include "util/Common.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "Common.hpp"

using namespace BIR;
using namespace BIR::BIREnumerations;
namespace vesyla
{
namespace filegen
{
class MatlabGenerator
{
private:
public:
  MatlabGenerator() {}
  ~MatlabGenerator() {}
  void generate(string directory_);

private:
  void gen_print_assign_statement(string filename_);
  void gen_print_assign_prim_func1(string filename_);
  void gen_print_assign_prim_func2(string filename_);
  void gen_print_assign_prim_func3(string filename_);
  void gen_print_assign_wt(string filename_);
  void gen_print_for_statement(string filename_);
  void gen_print_result(string filename_);
  void gen_print_storage_transfer(string filename_);
  void gen_print_value(string filename_);
  void gen_print_variable(string filename_);
};
} // namespace filegen
} // namespace vesyla

#endif // __VESYLA_FILEGEN_SRAM_IMAGE_GENERATOR_HPP__