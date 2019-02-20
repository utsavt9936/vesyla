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

#ifndef __VESYLA_CODEGEN_RACCU_VAR_MANAGER_HPP__
#define __VESYLA_CODEGEN_RACCU_VAR_MANAGER_HPP__

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"

namespace vesyla
{
namespace codegen
{
class RaccuVarManager
{
private:
	int _reg_num;
	map<string, int> _curr_index;

public:
	RaccuVarManager(int reg_num_ = 8) : _reg_num(reg_num_)
	{
		_curr_index = {};
	}
	int push(VIR::Coordinate coord_);
	int pop(VIR::Coordinate coord_);
	int top(VIR::Coordinate coord_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_RACCU_VAR_MANAGER_HPP__