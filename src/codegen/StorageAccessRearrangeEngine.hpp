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

#ifndef __VESYLA_CODEGEN_STORAGE_ACCESS_REARRANGE_ENGINE_HPP__
#define __VESYLA_CODEGEN_STORAGE_ACCESS_REARRANGE_ENGINE_HPP__

#include "Engine.hpp"
#include <queue>

#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace vesyla
{
namespace codegen
{

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, int> ControlFlowTree;

class StorageAccessRearrangeEngine : Engine
{
public:
	StorageAccessRearrangeEngine() = default;
	~StorageAccessRearrangeEngine() = default;
	void transform(cidfg::CidfgGraph &g_);

private:
	int get_affine_addr_level(BIR::RefiInstruction *instr_);
	int get_refi_level(cidfg::RefiInstrVertex *v_);
	bool move_refi(cidfg::CidfgGraph &g_, int instr_, int lh_, int lb_, int lt_);
	//void traverse(cidfg::CidfgGraph &g_, vector<vector<int>> vertices_, string loop_signature_l1_, string loop_signature_l2_, std::unordered_map<int, string> &refi2loops_, std::unordered_map<string, vector<int>> &loops_, std::set<int> &conflict_refis_);
	void traverse(cidfg::CidfgGraph &g_, std::set<int> &baned_refis, std::unordered_map<int, vector<int>> &refi2loop_);
	vector<int> get_imm_refis(ControlFlowTree &cft_, ControlFlowTree::vertex_descriptor vd_, std::unordered_map<int, ControlFlowTree::vertex_descriptor> &g2t_, std::unordered_map<ControlFlowTree::vertex_descriptor, int> t2g_, std::set<int> refis_);
	vector<int> get_all_refis(ControlFlowTree &cft_, ControlFlowTree::vertex_descriptor vd_, std::unordered_map<int, ControlFlowTree::vertex_descriptor> &g2t_, std::unordered_map<ControlFlowTree::vertex_descriptor, int> t2g_, std::set<int> refis_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_STORAGE_ACCESS_REARRANGE_ENGINE_HPP__