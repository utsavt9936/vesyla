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

#ifndef __VESYLA_CODE_GEN_BRANCH_MANAGER_HPP__
#define __VESYLA_CODE_GEN_BRANCH_MANAGER_HPP__

#include <stack>
#include <map>
#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"

using namespace std;
using namespace BIR;
using namespace VIR;

namespace vesyla{
namespace codegen{

struct BranchManagerRecord{
	IfStatement* _if_statement;
	DPUInstruction* _inst_cond;
	BranchInstruction * _inst_branch;
	JumpInstruction * _inst_jump;
	WaitInstruction * _inst_dummy;
	vector<Instruction*> _inst_list_then;
	vector<Instruction*> _inst_list_else;
};

class BranchManager1{
private:
	stack<map<string, BranchManagerRecord>> _branch_store;

public:
	bool enableFalseAddrCalc;
	bool enableJumpAddrCalc;
	bool isElsePartRegion;

public:
	BranchManager1() : enableFalseAddrCalc(false), enableJumpAddrCalc(false), isElsePartRegion(false){}
	void push(IfStatement* if_statemenmt_);
	void pop();
	IfStatement* get_curr_if_statement();
	DPUInstruction* get_curr_inst_cond(const Coordinate coord_);
	BranchInstruction* get_curr_inst_branch(const Coordinate coord_);
	JumpInstruction* get_curr_inst_jump(const Coordinate coord_);
	WaitInstruction* get_curr_inst_dummy_wait(const Coordinate coord_);
	void set_curr_inst_cond(const Coordinate coord_, DPUInstruction* inst_cond_);
	void set_curr_inst_branch(const Coordinate coord_, BranchInstruction* inst_branch_);
	void set_curr_inst_jump(const Coordinate coord_, JumpInstruction* inst_branch_);
	void set_curr_inst_dummy_wait(const Coordinate coord_, WaitInstruction * inst_dummy_wait_);

//	vector<Instruction*> curr_inst_list_then(const Coordinate coord_);
//	vector<Instruction*> curr_inst_list_else(const Coordinate coord_);
};

}
}


#endif //__VESYLA_CODE_GEN_BRANCH_MANAGER_HPP__
