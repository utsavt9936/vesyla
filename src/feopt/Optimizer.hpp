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

#ifndef __VESYLA_FEOPT_OPTIMIZER_HPP__
#define __VESYLA_FEOPT_OPTIMIZER_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"
#include "ExprSimpEngine.hpp"
#include "SrcConvEngine.hpp"
#include "RwiMergeEngine.hpp"
#include "BindEngine.hpp"
#include "DependencyAnalyzeEngine.hpp"
#include "CleanEngine.hpp"
#include "cidfg/ScriptGenerator.hpp"

namespace vesyla
{
namespace feopt
{
class Optimizer
{
public:
	Optimizer();
	~Optimizer();
	void optimize(cidfg::CidfgGraph &g_);

private:
	void to_dot_graph(cidfg::CidfgGraph &g_, int stage_);
	void gen_script();
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_OPTIMIZER_HPP__