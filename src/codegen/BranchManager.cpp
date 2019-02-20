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

#include "BranchManager.hpp"

namespace vesyla{
namespace codegen{

void BranchManager1::push(IfStatement* if_statement_){
	map<string, BranchManagerRecord> m;
	for(auto & coord : if_statement_->conditionPragma()->coordinates){
		string coord_str = to_string(coord.row)+"_"+to_string(coord.column);
		BranchManagerRecord rec;
		rec._if_statement = if_statement_;
		m[coord_str] = rec;
	}
	_branch_store.push(m);
}

void BranchManager1::pop(){
	CHECK(!_branch_store.empty());
	_branch_store.pop();
}

IfStatement* BranchManager1::get_curr_if_statement(){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord> m =_branch_store.top();
	auto it=m.begin();
	if(it!=m.end()){
		BranchManagerRecord rec = it->second;
		return rec._if_statement;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch";
	}
	return NULL;
}

DPUInstruction* BranchManager1::get_curr_inst_cond(Coordinate coord_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord> m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		BranchManagerRecord rec = it->second;
		return rec._inst_cond;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
	return NULL;
}

BranchInstruction* BranchManager1::get_curr_inst_branch(Coordinate coord_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord> m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		BranchManagerRecord rec = it->second;
		return rec._inst_branch;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
	return NULL;
}

JumpInstruction* BranchManager1::get_curr_inst_jump(Coordinate coord_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord> m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		BranchManagerRecord rec = it->second;
		return rec._inst_jump;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
	return NULL;
}

WaitInstruction* BranchManager1::get_curr_inst_dummy_wait(Coordinate coord_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord> m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		BranchManagerRecord rec = it->second;
		return rec._inst_dummy;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
	return NULL;
}

void BranchManager1::set_curr_inst_cond(Coordinate coord_, DPUInstruction* inst_cond_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord>& m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		it->second._inst_cond = inst_cond_;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
}

void BranchManager1::set_curr_inst_branch(Coordinate coord_, BranchInstruction* inst_branch_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord>& m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		it->second._inst_branch = inst_branch_;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
}

void BranchManager1::set_curr_inst_jump(Coordinate coord_, JumpInstruction* inst_jump_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord>& m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		it->second._inst_jump = inst_jump_;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
}

void BranchManager1::set_curr_inst_dummy_wait(Coordinate coord_, WaitInstruction* inst_dummy_wait_){
	CHECK(!_branch_store.empty());
	map<string, BranchManagerRecord>& m =_branch_store.top();
	string coord_str = to_string(coord_.row)+"_"+to_string(coord_.column);
	auto it = m.find(coord_str);
	if(it!=m.end()){
		it->second._inst_dummy = inst_dummy_wait_;
	}else{
		LOG(FATAL) << "Branch manager can't find current branch on"
				<< "[" << coord_.row << "," << coord_.column << "]";
	}
}

}
}
