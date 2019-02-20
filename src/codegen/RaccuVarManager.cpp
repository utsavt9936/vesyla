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

#include "RaccuVarManager.hpp"

namespace vesyla
{
namespace codegen
{
int RaccuVarManager::push(VIR::Coordinate coord_)
{
	string signature = to_string(coord_.row) + "_" + to_string(coord_.column);
	if (_curr_index.find(signature) != _curr_index.end())
	{
		int idx = _curr_index[signature];
		CHECK_LT(idx, _reg_num) << "Too many raccu variables!";
		_curr_index[signature]++;
		return idx;
	}
	else
	{
		_curr_index[signature] = 1;
		return 0;
	}
}

int RaccuVarManager::pop(VIR::Coordinate coord_)
{
	string signature = to_string(coord_.row) + "_" + to_string(coord_.column);
	if (_curr_index.find(signature) != _curr_index.end())
	{
		int idx = _curr_index[signature];
		CHECK_GT(idx, 0) << "No raccu variables is availabe to be removed!";
		_curr_index[signature]--;
		return idx;
	}
	else
	{
		LOG(FATAL) << "No raccu variables is availabe to be removed!";
		return -1;
	}
}

int RaccuVarManager::top(VIR::Coordinate coord_)
{
	string signature = to_string(coord_.row) + "_" + to_string(coord_.column);
	if (_curr_index.find(signature) != _curr_index.end())
	{
		int idx = _curr_index[signature];
		return idx;
	}
	else
	{
		return 0;
	}
}
} // namespace codegen
} // namespace vesyla