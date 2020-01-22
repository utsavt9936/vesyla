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

#include "StorageAccessRearrangeEngine.hpp"

namespace vesyla
{
namespace codegen
{

void StorageAccessRearrangeEngine::traverse(cidfg::CidfgGraph &g_, std::set<int> &baned_refis, std::unordered_map<int, vector<int>> &refi2loop_)
{

	ControlFlowTree cft;

	std::unordered_map<int, vector<int>> loop_signatures;
	std::set<int> loops;
	std::set<int> branches;
	std::set<int> refis;

	// Find the hierarchical vertices for loops and branches
	for (auto gv : g_.get_vertices())
	{
		if (gv->vertex_type == cidfg::Vertex::HIERARCHICAL_INSTR_VERTEX)
		{
			cidfg::HierarchicalInstrVertex *v = static_cast<cidfg::HierarchicalInstrVertex *>(gv);
			int in_edge_0 = g_.get_in_edge(v->id, 0);
			int out_edge_0 = g_.get_out_edge(v->id, 0);

			if (in_edge_0 >= 0)
			{
				int in_v_0 = g_.get_edge(in_edge_0)->src_id;
				if (in_v_0 >= 0)
				{
					cidfg::Vertex *vbr = g_.get_vertex(in_v_0);
					if (vbr->vertex_type == cidfg::Vertex::BRANCH_INSTR_VERTEX)
					{
						string branch_signature = to_string(vbr->id) + "_" + to_string(v->id);
						branches.insert(v->id);
					}
				}
			}
			if (in_edge_0 >= 0 && out_edge_0 >= 0)
			{
				int in_v_0 = g_.get_edge(in_edge_0)->src_id;
				int out_v_0 = g_.get_edge(out_edge_0)->dest_id;
				if (in_v_0 >= 0 && out_v_0 >= 0)
				{
					cidfg::Vertex *vh = g_.get_vertex(in_v_0);
					cidfg::Vertex *vt = g_.get_vertex(out_v_0);
					if (vh->vertex_type == cidfg::Vertex::LOOPH_INSTR_VERTEX && vt->vertex_type == cidfg::Vertex::LOOPT_INSTR_VERTEX)
					{
						loop_signatures[v->id] = {vh->id, v->id, vt->id};
						loops.insert(v->id);
					}
				}
			}
		}
		else if (gv->vertex_type == cidfg::Vertex::REFI_INSTR_VERTEX)
		{
			cidfg::RefiInstrVertex *v = static_cast<cidfg::RefiInstrVertex *>(gv);
			refis.insert(v->id);
		}
	}

	std::unordered_map<int, ControlFlowTree::vertex_descriptor> g2t;
	std::unordered_map<ControlFlowTree::vertex_descriptor, int> t2g;

	for (auto gv : g_.get_vertices())
	{
		if (gv->vertex_type == cidfg::Vertex::REFI_INSTR_VERTEX)
		{
			cidfg::RefiInstrVertex *v = static_cast<cidfg::RefiInstrVertex *>(gv);
			if (g2t.find(v->id) == g2t.end())
			{
				ControlFlowTree::vertex_descriptor vv = add_vertex(v->id, cft);
				g2t[v->id] = vv;
				t2g[vv] = v->id;
				if (get_refi_level(v) == 2)
				{
					baned_refis.insert(v->id);
				}
			}
		}
		else if (gv->vertex_type == cidfg::Vertex::HIERARCHICAL_INSTR_VERTEX)
		{
			cidfg::HierarchicalInstrVertex *v = static_cast<cidfg::HierarchicalInstrVertex *>(gv);
			if (g2t.find(v->id) == g2t.end())
			{
				ControlFlowTree::vertex_descriptor vv = add_vertex(v->id, cft);
				g2t[v->id] = vv;
				t2g[vv] = v->id;
			}
			for (int i = 0; i < v->children.size(); i++)
			{
				for (int j = 0; j < v->children[i].size(); j++)
				{
					if (g2t.find(v->children[i][j]) == g2t.end())
					{
						ControlFlowTree::vertex_descriptor vv = add_vertex(v->children[i][j], cft);
						g2t[v->children[i][j]] = vv;
						t2g[vv] = v->children[i][j];
					}
					add_edge(g2t[v->id], g2t[v->children[i][j]], cft);
				}
			}
		}
	}

	// Transform the CFT to another CFT without general hierarchical vertices. Only
	// LOOP and BRANCH body are allowed as hierarchical vertices.
	ControlFlowTree::vertex_iterator vi, vi_end;
	bool flag_changed = false;
	do
	{
		flag_changed = false;
		for (tie(vi, vi_end) = vertices(cft); vi != vi_end; vi++)
		{
			if (loops.find(t2g[*vi]) != loops.end() || branches.find(t2g[*vi]) != branches.end() || refis.find(t2g[*vi]) != refis.end())
			{
				continue;
			}

			vector<ControlFlowTree::vertex_descriptor> vec_iv, vec_ov;
			vector<vector<ControlFlowTree::vertex_descriptor>> vec_e;
			ControlFlowTree::in_edge_iterator iei, iei_end;
			ControlFlowTree::out_edge_iterator oei, oei_end;
			for (tie(iei, iei_end) = in_edges(*vi, cft); iei != iei_end; iei++)
			{
				vec_iv.push_back(source(*iei, cft));
				vec_e.push_back({source(*iei, cft), *vi});
			}
			for (tie(oei, oei_end) = out_edges(*vi, cft); oei != oei_end; oei++)
			{
				vec_ov.push_back(target(*oei, cft));
				vec_e.push_back({*vi, target(*oei, cft)});
			}

			for (auto iv : vec_iv)
			{
				for (auto ov : vec_ov)
				{
					add_edge(iv, ov, cft);
				}
			}

			for (auto e : vec_e)
			{
				remove_edge(e[0], e[1], cft);
				flag_changed = true;
			}
		}
	} while (flag_changed == true);

	// Ban REFIs that can't be moved
	for (tie(vi, vi_end) = vertices(cft); vi != vi_end; vi++)
	{

		vector<int> imm_refis = get_imm_refis(cft, *vi, g2t, t2g, refis);
		vector<int> all_refis = get_all_refis(cft, *vi, g2t, t2g, refis);

		// if the node doesn't have a parent, continue
		if (in_degree(*vi, cft) <= 0 && refis.find(t2g[*vi]) != refis.end())
		{
			baned_refis.insert(t2g[*vi]);
			continue;
		}

		if (branches.find(t2g[*vi]) != branches.end())
		{
			for (int vrf0 : imm_refis)
			{
				baned_refis.insert(vrf0);
			}
			continue;
		}

		if (loops.find(t2g[*vi]) != loops.end())
		{
			for (int vrf0 : imm_refis)
			{
				cidfg::RefiInstrVertex *rf0 = static_cast<cidfg::RefiInstrVertex *>(g_.get_vertex(vrf0));
				for (int vrf1 : all_refis)
				{
					if (vrf1 == vrf0)
					{
						continue;
					}
					cidfg::RefiInstrVertex *rf1 = static_cast<cidfg::RefiInstrVertex *>(g_.get_vertex(vrf1));
					if (rf0->coord == rf1->coord &&
							static_cast<BIR::RefiInstruction *>(rf0->instr)->portNo == static_cast<BIR::RefiInstruction *>(rf1->instr)->portNo)
					{
						baned_refis.insert(vrf0);
						break;
					}
				}
			}
		}
	}

	// Fill refi2loop
	for (tie(vi, vi_end) = vertices(cft); vi != vi_end; vi++)
	{
		if (refis.find(t2g[*vi]) != refis.end())
		{
			if (in_degree(*vi, cft) == 1)
			{
				ControlFlowTree::in_edge_iterator iei, iei_end;
				for (tie(iei, iei_end) = in_edges(*vi, cft); iei != iei_end; iei++)
				{
					ControlFlowTree::vertex_descriptor loop_v = source(*iei, cft);
					if (loops.find(t2g[loop_v]) != loops.end())
					{
						refi2loop_[t2g[*vi]] = loop_signatures[t2g[loop_v]];
					}
				}
			}
		}
	}
}

vector<int> StorageAccessRearrangeEngine::get_imm_refis(ControlFlowTree &cft_, ControlFlowTree::vertex_descriptor vd_, std::unordered_map<int, ControlFlowTree::vertex_descriptor> &g2t_, std::unordered_map<ControlFlowTree::vertex_descriptor, int> t2g_, std::set<int> refis_)
{
	vector<int> vec;
	ControlFlowTree::out_edge_iterator oei, oei_end;
	for (tie(oei, oei_end) = out_edges(vd_, cft_); oei != oei_end; oei++)
	{
		if (refis_.find(t2g_[target(*oei, cft_)]) != refis_.end())
		{
			vec.push_back(t2g_[target(*oei, cft_)]);
		}
	}
	return vec;
}
vector<int> StorageAccessRearrangeEngine::get_all_refis(ControlFlowTree &cft_, ControlFlowTree::vertex_descriptor vd_, std::unordered_map<int, ControlFlowTree::vertex_descriptor> &g2t_, std::unordered_map<ControlFlowTree::vertex_descriptor, int> t2g_, std::set<int> refis_)
{
	vector<int> vec;
	ControlFlowTree::out_edge_iterator oei, oei_end;
	for (tie(oei, oei_end) = out_edges(vd_, cft_); oei != oei_end; oei++)
	{
		if (refis_.find(t2g_[target(*oei, cft_)]) != refis_.end())
		{
			vec.push_back(t2g_[target(*oei, cft_)]);
		}

		vector<int> vec1;
		vec1 = get_all_refis(cft_, target(*oei, cft_), g2t_, t2g_, refis_);
		for (auto x : vec1)
		{
			vec.push_back(x);
		}
	}
	return vec;
}

// void StorageAccessRearrangeEngine::traverse(cidfg::CidfgGraph &g_, vector<vector<int>> vertices_, string loop_signature_l1_, string loop_signature_l2_, std::unordered_map<int, string> &refi2loops_, std::unordered_map<string, vector<int>> &loops_, std::set<int> &conflict_refis_)
// {
// 	for (int i = 0; i < vertices_.size(); i++)
// 	{
// 		for (int j = 0; j < vertices_[i].size(); j++)
// 		{
// 			cidfg::Vertex *v = g_.get_vertex(vertices_[i][j]);
// 			if (v->vertex_type == cidfg::Vertex::HIERARCHICAL_INSTR_VERTEX)
// 			{
// 				string new_loop_signature_l2 = loop_signature_l2_;
// 				string new_loop_signature_l1 = loop_signature_l1_;

// 				// get its in0 and out0
// 				int in_edge_0 = g_.get_in_edge(v->id, 0);
// 				int out_edge_0 = g_.get_out_edge(v->id, 0);
// 				if (in_edge_0 >= 0 && out_edge_0 >= 0)
// 				{
// 					int in_v_0 = g_.get_edge(in_edge_0)->src_id;
// 					int out_v_0 = g_.get_edge(out_edge_0)->dest_id;
// 					if (in_v_0 >= 0 && out_v_0 >= 0)
// 					{
// 						cidfg::Vertex *vh = g_.get_vertex(in_v_0);
// 						cidfg::Vertex *vt = g_.get_vertex(out_v_0);
// 						if (vh->vertex_type == cidfg::Vertex::LOOPH_INSTR_VERTEX && vt->vertex_type == cidfg::Vertex::LOOPT_INSTR_VERTEX)
// 						{
// 							new_loop_signature_l2 = new_loop_signature_l1;
// 							new_loop_signature_l1 = to_string(vh->id) + "_" + to_string(v->id) + "_" + to_string(vt->id);
// 							loops_[new_loop_signature_l1] = {vh->id, v->id, vt->id};
// 						}
// 					}
// 				}
// 				traverse(g_, static_cast<cidfg::HierarchicalVertex *>(v)->children, new_loop_signature_l1, new_loop_signature_l2, refi2loops_, loops_, conflict_refis_);
// 			}
// 			else if (v->vertex_type == cidfg::Vertex::REFI_INSTR_VERTEX)
// 			{
// 				BIR::RefiInstruction *instr = static_cast<BIR::RefiInstruction *>(static_cast<cidfg::RefiInstrVertex *>(v)->instr);
// 				bool conflict = false;
// 				for (auto &rf : refi2loops_)
// 				{
// 					if ((rf.second == loop_signature_l1_ && !static_cast<cidfg::RefiInstrVertex *>(v)->l1_linker.is_valid) || (rf.second == loop_signature_l2_ && static_cast<cidfg::RefiInstrVertex *>(v)->l1_linker.is_valid))
// 					{
// 						if (static_cast<cidfg::RefiInstrVertex *>(g_.get_vertex(rf.first))->coord == static_cast<cidfg::RefiInstrVertex *>(v)->coord &&
// 								static_cast<BIR::RefiInstruction *>(static_cast<cidfg::RefiInstrVertex *>(g_.get_vertex(rf.first))->instr)->portNo == instr->portNo)
// 						{
// 							conflict = true;
// 							conflict_refis_.insert(rf.first);
// 							conflict_refis_.insert(v->id);
// 						}
// 					}
// 				}

// 				if (get_refi_level(static_cast<cidfg::RefiInstrVertex *>(v)) == 2)
// 				{
// 					conflict = true;
// 					conflict_refis_.insert(v->id);
// 				}

// 				if (conflict == true)
// 				{
// 					continue;
// 				}

// 				if (static_cast<cidfg::RefiInstrVertex *>(v)->l1_linker.is_valid)
// 				{
// 					if (loop_signature_l2_ == "")
// 					{
// 						conflict_refis_.insert(v->id);
// 					}
// 					else
// 					{
// 						refi2loops_[v->id] = loop_signature_l2_;
// 					}
// 				}
// 				else
// 				{
// 					if (loop_signature_l1_ == "")
// 					{
// 						conflict_refis_.insert(v->id);
// 					}
// 					else
// 					{
// 						refi2loops_[v->id] = loop_signature_l1_;
// 					}
// 				}
// 			}
// 		}
// 	}
// }

void StorageAccessRearrangeEngine::transform(cidfg::CidfgGraph &g_)
{
	bool flag_changed = true;
	std::set<int> ban_refis;
	while (flag_changed)
	{
		flag_changed = false;
		std::unordered_map<int, vector<int>> refi2loops;
		std::set<int> conflict_refis;
		traverse(g_, conflict_refis, refi2loops);
		queue<int> refi_queue;
		for (auto &r : refi2loops)
		{
			if (conflict_refis.find(r.first) == conflict_refis.end() && ban_refis.find(r.first) == ban_refis.end())
			{
				refi_queue.push(r.first);
			}
		}
		while (!refi_queue.empty())
		{
			int refi_id = refi_queue.front();
			int lh_id = refi2loops[refi_id][0];
			int lb_id = refi2loops[refi_id][1];
			int lt_id = refi2loops[refi_id][2];
			if (move_refi(g_, refi_id, lh_id, lb_id, lt_id))
			{
				flag_changed = true;
			}
			else
			{
				ban_refis.insert(refi_id);
			}
			refi_queue.pop();
		}
	}
}

int StorageAccessRearrangeEngine::get_affine_addr_level(BIR::RefiInstruction *instr_)
{
	bool l1_start_addr_static = instr_->startAddress.isStatic;
	bool l1_step_val_static = instr_->stepValue.isStatic;
	bool l1_iteration_static = instr_->numberOfAddress.isStatic;
	bool l2_iteration_static = instr_->numberOfAddress.isStatic;
	int l1_iteration_num = instr_->numberOfAddress.value;
	int l2_iteration_num = instr_->numberOfRepetition.value;
	bool is_dimarch = instr_->isDimarchMode;

	if ((l2_iteration_static == true) && (l2_iteration_num == 0) && (l1_iteration_static == true) && (l1_iteration_num == 0) && (l1_start_addr_static == true) && (l1_step_val_static == true))
	{
		return 0;
	}

	if (l2_iteration_static == true && l2_iteration_num == 0 && l1_iteration_static == true && l1_start_addr_static == true && l1_step_val_static == true)
	{
		return 1;
	}

	return 2;
}

int StorageAccessRearrangeEngine::get_refi_level(cidfg::RefiInstrVertex *v_)
{
	if (v_->l2_linker.is_valid || get_affine_addr_level(static_cast<BIR::RefiInstruction *>(v_->instr)) == 2)
	{
		return 2;
	}
	else if (v_->l1_linker.is_valid || get_affine_addr_level(static_cast<BIR::RefiInstruction *>(v_->instr)) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool StorageAccessRearrangeEngine::move_refi(cidfg::CidfgGraph &g_, int refi_, int lh_, int lb_, int lt_)
{
	cidfg::Vertex *v;
	v = g_.get_vertex(refi_);
	CHECK_EQ(v->vertex_type, cidfg::Vertex::REFI_INSTR_VERTEX);
	cidfg::RefiInstrVertex *refi = static_cast<cidfg::RefiInstrVertex *>(v);
	int level = get_refi_level(refi);
	BIR::RefiInstruction *instr = static_cast<BIR::RefiInstruction *>(refi->instr);

	if (level >= 2)
	{
		return false;
	}

	v = g_.get_vertex(lh_);
	CHECK_EQ(v->vertex_type, cidfg::Vertex::LOOPH_INSTR_VERTEX);
	cidfg::LoophInstrVertex *lh = static_cast<cidfg::LoophInstrVertex *>(v);
	v = g_.get_vertex(lb_);
	CHECK_EQ(v->vertex_type, cidfg::Vertex::HIERARCHICAL_INSTR_VERTEX);
	cidfg::HierarchicalInstrVertex *lb = static_cast<cidfg::HierarchicalInstrVertex *>(v);
	v = g_.get_vertex(lt_);
	CHECK_EQ(v->vertex_type, cidfg::Vertex::LOOPT_INSTR_VERTEX);
	cidfg::LooptInstrVertex *lt = static_cast<cidfg::LooptInstrVertex *>(v);

	if (!static_cast<BIR::LoopHeaderInstruction *>(lh->instr)->isStatic)
	{
		return false;
	}

	int loop_start = static_cast<BIR::LoopHeaderInstruction *>(lh->instr)->startValue;
	int loop_step = static_cast<BIR::LoopTailInstruction *>(lt->instr)->stepValue;
	int loop_iteration = static_cast<BIR::LoopHeaderInstruction *>(lh->instr)->iterationNumber;

	if (level == 1)
	{
		refi->l2_linker.is_valid = true;
		refi->l2_linker.lh = lh_;
		refi->l2_linker.lb = lb_;
		refi->l2_linker.lt = lt_;
		instr->repetitionOffset = 0;
		instr->numberOfRepetition.value = loop_iteration - 1;
		return true;
	}

	if (level == 0)
	{
		refi->l1_linker.is_valid = true;
		refi->l1_linker.lh = lh_;
		refi->l1_linker.lb = lb_;
		refi->l1_linker.lt = lt_;
		instr->stepValue.value = 0;
		instr->numberOfAddress.value = loop_iteration - 1;
		return true;
	}

	return false;
}

} // namespace codegen
} // namespace vesyla