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

#ifndef __VESYLA_SCHEDULE_CONSTRAINT_PROGRAMMING_ENGINE_HPP__
#define __VESYLA_SCHEDULE_CONSTRAINT_PROGRAMMING_ENGINE_HPP__

#include "Engine.hpp"
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/kernel.hh>
#include <gecode/minimodel.hh>

namespace vesyla
{
namespace schedule
{
/**
	* \brief Scheduling Engine using constraint programming (Gecode).
	*/
class ConstraintProgrammingEngine : public Engine
{
public:
	ConstraintProgrammingEngine();
	ConstraintProgrammingEngine(Descriptor *ptr_desc_);
	~ConstraintProgrammingEngine();

public:
	bool schedule_graph(Graph &g_, Rot &global_rot_in_, int &min_end_time_);
};

// Here start define the real solver class
class Solver : public Gecode::IntMinimizeSpace
{
protected:
	Gecode::IntVarArray _scheduled_time_list;
	Gecode::IntVar _latency;
	std::unordered_map<string, int> _vertex_map;

public:
	Solver(Graph &g_, Rot &global_rot_in_, int &min_end_time_, int max_scheduled_time);
	Solver(Solver &s);
	virtual Gecode::Space *copy(void);
	string solution_to_str(void) const;
	void fill_scheduled_time(Graph &g_);
	virtual Gecode::IntVar cost(void) const;
	virtual void constrain(const Gecode::Space &b_);
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_CONSTRAINT_PROGRAMMING_ENGINE_HPP__