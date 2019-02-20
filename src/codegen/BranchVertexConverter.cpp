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

#include "BranchVertexConverter.hpp"
using namespace boost;
using namespace BIR;
using namespace BIR::BIREnumerations;
namespace vesyla
{
namespace codegen
{
BranchVertexConverter::BranchVertexConverter()
{
}
BranchVertexConverter::~BranchVertexConverter()
{
}

void BranchVertexConverter::convert(cidfg::CidfgGraph &g_)
{
	std::set<int> remove_vertices;
	for (auto &v : g_.get_vertices())
	{
		if (v->vertex_type == cidfg::Vertex::BRANCH_VERTEX)
		{
			int parent_id;
			int child_index;
			g_.get_parent(v->id, parent_id, child_index);

			cidfg::HierarchicalVertex *vv = static_cast<cidfg::HierarchicalVertex *>(v);

			cidfg::HierarchicalInstrVertex v_branch;
			cidfg::BranchInstrVertex v_brn;
			cidfg::HierarchicalInstrVertex v_body;
			cidfg::HierarchicalInstrVertex v_then1;
			cidfg::JumpInstrVertex v_jump;
			cidfg::WaitInstrVertex v_wait;
			v_branch.coord = v->coord;
			v_brn.coord = v->coord;
			v_body.coord = v->coord;
			v_then1.coord = v->coord;
			v_jump.coord = v->coord;
			v_wait.coord = v->coord;

			BIR::WaitInstruction *i_wait = CREATE_OBJECT_B(WaitInstruction);
			i_wait->numberOfCycles(0, true);
			v_wait.instr = i_wait;

			BIR::JumpInstruction *i_jump = CREATE_OBJECT_B(JumpInstruction);
			i_jump->jumpAddressInstruction = i_wait;
			v_jump.instr = i_jump;

			BIR::BranchInstruction *i_brn = CREATE_OBJECT_B(BranchInstruction);
			i_brn->falseAddressInstruction = i_jump;
			v_brn.instr = i_brn;

			int id_v_branch = g_.add_vertex(v_branch, parent_id, child_index);
			int id_v_brn = g_.add_vertex(v_brn, id_v_branch, 0);
			int id_v_body = g_.add_vertex(v_body, id_v_branch, 0);
			int id_v_wait = g_.add_vertex(v_wait, id_v_branch, 0);
			int id_v_then1 = g_.add_vertex(v_then1, id_v_body, 0);
			int id_v_jump = g_.add_vertex(v_jump, id_v_body, 0);

			cidfg::HierarchicalInstrVertex *ptr_v_branch = static_cast<cidfg::HierarchicalInstrVertex *>(g_.get_vertex(id_v_branch));
			cidfg::HierarchicalInstrVertex *ptr_v_brn = static_cast<cidfg::HierarchicalInstrVertex *>(g_.get_vertex(id_v_brn));
			cidfg::HierarchicalInstrVertex *ptr_v_body = static_cast<cidfg::HierarchicalInstrVertex *>(g_.get_vertex(id_v_body));
			cidfg::HierarchicalInstrVertex *ptr_v_then1 = static_cast<cidfg::HierarchicalInstrVertex *>(g_.get_vertex(id_v_then1));

			bool flag_reverse_then_else = false;
			cidfg::DpuInstrVertex *cv = static_cast<cidfg::DpuInstrVertex *>(g_.get_vertex(g_.get_edge(g_.get_in_edge(v->id, 0))->src_id));

			char char_comparator[10] = {'\0'};
			if (strncmp(static_cast<BIR::DPUInstruction *>(cv->instr)->mode.c_str(), "silago_dpu_comparison_with_constant_", strlen("silago_dpu_comparison_with_constant_")) == 0)
			{
				sscanf(static_cast<BIR::DPUInstruction *>(cv->instr)->mode.c_str(), "silago_dpu_comparison_with_constant_%s", char_comparator);
				static_cast<BIR::DPUInstruction *>(cv->instr)->mode = "silago_dpu_comparison_with_constant";
			}
			else if (strncmp(static_cast<BIR::DPUInstruction *>(cv->instr)->mode.c_str(), "silago_dpu_comparison_", strlen("silago_dpu_comparison_")) == 0)
			{
				sscanf(static_cast<BIR::DPUInstruction *>(cv->instr)->mode.c_str(), "silago_dpu_comparison_%s", char_comparator);
				static_cast<BIR::DPUInstruction *>(cv->instr)->mode = "silago_dpu_comparison";
			}
			else
			{
				LOG(FATAL) << "Non comparison operation before BRANCH!";
			}

			string str_comparator(char_comparator);
			if (str_comparator == "==")
			{
				flag_reverse_then_else = false;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->mode = bmEqual;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->modeValue = 2;
			}
			else if (str_comparator == "~=")
			{
				flag_reverse_then_else = true;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->mode = bmEqual;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->modeValue = 2;
			}
			else if (str_comparator == "<")
			{
				flag_reverse_then_else = true;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->mode = bmGreaterOrEqual;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->modeValue = 3;
			}
			else if (str_comparator == "<=")
			{
				flag_reverse_then_else = true;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->mode = bmGreater;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->modeValue = 1;
			}
			else if (str_comparator == ">")
			{
				flag_reverse_then_else = false;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->mode = bmGreater;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->modeValue = 1;
			}
			else if (str_comparator == ">=")
			{
				flag_reverse_then_else = false;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->mode = bmGreaterOrEqual;
				static_cast<BIR::BranchInstruction *>(ptr_v_brn->instr)->modeValue = 3;
			}
			else
			{
				LOG(FATAL) << "Unreconganized comparator: " << str_comparator;
			}

			ptr_v_body->children.resize(2);
			if (flag_reverse_then_else == false)
			{
				CHECK_EQ(vv->children.size(), 2); // Branch should always has then and else part
				for (auto &id : vv->children[0])
				{
					ptr_v_then1->add_child(0, id);
				}
				for (auto &id : vv->children[1])
				{
					ptr_v_body->add_child(1, id);
				}
			}
			else
			{
				// swap then and else part
				CHECK_EQ(vv->children.size(), 2); // Branch should always has then and else part
				for (auto &id : vv->children[0])
				{
					ptr_v_body->add_child(1, id);
				}
				for (auto &id : vv->children[1])
				{
					ptr_v_then1->add_child(0, id);
				}
			}

			cidfg::Edge e0(id_v_brn, 0, id_v_body, 0, "", cidfg::Edge::DEPENDENCY, 1, 1);
			cidfg::Edge e1(id_v_body, 0, id_v_wait, 0, "", cidfg::Edge::DEPENDENCY, 1, INT_MAX);
			cidfg::Edge e2(id_v_then1, 0, id_v_jump, 0, "", cidfg::Edge::DEPENDENCY, 1, INT_MAX);
			g_.add_edge(e0);
			g_.add_edge(e1);
			g_.add_edge(e2);

			for (auto &e : g_.get_edges())
			{
				if (e->src_id == v->id)
				{
					e->src_id = id_v_branch;
				}
				if (e->dest_id == v->id)
				{
					if (e->dest_port == 0)
					{
						e->dest_id = id_v_brn;
						e->edge_type = cidfg::Edge::DEPENDENCY;
						e->d_lo = 1;
						e->d_hi = 1;
					}
					else
					{
						e->dest_id = id_v_branch;
					}
				}
			}

			vv->children.clear();
			remove_vertices.insert(v->id);
		}
	}

	for (auto &id : remove_vertices)
	{
		g_.del_vertex(id);
	}
} // namespace codegen

} // namespace codegen
} // namespace vesyla