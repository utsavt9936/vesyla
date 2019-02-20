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

#ifndef __VESYLA_FILEGEN_MANAS_GENERATOR_HPP__
#define __VESYLA_FILEGEN_MANAS_GENERATOR_HPP__

#include <boost/algorithm/string.hpp>
#include "util/Common.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "Common.hpp"

using namespace BIR;
using namespace BIR::BIREnumerations;

namespace vesyla
{
namespace filegen
{
class ManasGenerator
{
private:
	string create_refi1_instr(Refi1Instruction *refi1Inst_);
	string create_refi2_instr(Refi2Instruction *refi2Inst_);
	string create_refi3_instr(Refi3Instruction *refi3Inst_);
	string create_raccu_instr(RACCUInstruction *raccuInst_);
	string create_jump_instr(JumpInstruction *jumpInst_);
	string create_looph_instr(LoopHeaderInstruction *loopHeaderInst_);
	string create_loopt_instr(LoopTailInstruction *loopTailInst_);
	string create_branch_instr(BranchInstruction *branchInst_);
	string create_dpu_instr(DPUInstruction *dpuInst_);
	string create_wait_instr(WaitInstruction *waitInst_);
	string create_route_instr(RouteInstruction *routeInst_);
	string create_swb_instr(SWBInstruction *swbInst_);
	string create_sram_instr(BIR::SRAMInstruction *sramInst_);

public:
	ManasGenerator() {}
	~ManasGenerator() {}
	void generate(map<string, vector<Instruction *>> instr_lists, string filename);
};
} // namespace filegen
} // namespace vesyla

#endif // __VESYLA_FILEGEN_MANAS_GENERATOR_HPP__