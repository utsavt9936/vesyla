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

#ifndef __VESYLA_FEOPT_SRC_CONV_ENGINE_HPP__
#define __VESYLA_FEOPT_SRC_CONV_ENGINE_HPP__

#include "Engine.hpp"

namespace vesyla
{
namespace feopt
{
/**
 * This class convert the variable declaration to source vertices.
 * Variable decleared as Register file vector or SRAM vector will be converted to
 * corresponding source vertices.
 * 
 * Declearation can be done by several ways.
 *  1) directly listing the elements;
 *  2) using zeros() or ones() function;
 *  3) using fi() to specify fixed number;
 */
class SrcConvEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);

private:
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_SRC_CONV_ENGINE_HPP__