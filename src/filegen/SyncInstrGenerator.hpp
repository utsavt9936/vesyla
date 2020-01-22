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

#ifndef __VESYLA_FILEGEN_SYNC_INSTR_GENERATOR_HPP__
#define __VESYLA_FILEGEN_SYNC_INSTR_GENERATOR_HPP__

#include "util/Common.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "Common.hpp"

using namespace BIR;
using namespace BIR::BIREnumerations;
namespace vesyla
{
namespace filegen
{
class SyncInstrGenerator
{
private:
public:
	SyncInstrGenerator() {}
	~SyncInstrGenerator() {}
	void generate(map<string, vector<BIR::Instruction *>> instr_lists, string filename_);

private:
	string dump_instr(BIR::Instruction *instruction_, int index_, int &offset_, int cell_init_delay_);
};
} // namespace filegen
} // namespace vesyla

#endif // __VESYLA_FILEGEN_SYNC_INSTR_GENERATOR_HPP__