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

#ifndef __VESYLA_FEOPT_ENGINE_HPP__
#define __VESYLA_FEOPT_ENGINE_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"

namespace vesyla
{
namespace feopt
{
class Engine
{
public:
	Engine();
	virtual ~Engine() = 0;
	virtual void transform(cidfg::CidfgGraph &g_) = 0;
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_ENGINE_HPP__