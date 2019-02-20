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

#ifndef __VESYLA_CODEGEN_SRAM_ADDRESS_TRANSFORMER_HPP__
#define __VESYLA_CODEGEN_SRAM_ADDRESS_TRANSFORMER_HPP__

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"

namespace vesyla
{
namespace codegen
{
class SramAddressTransformer
{
private:
	int _agu_num;
	int _width;

public:
	SramAddressTransformer(int agu_num_ = 16, int width_ = 16) : _agu_num(agu_num_), _width(width_) {}
	~SramAddressTransformer() {}
	VIR::Address transform(VIR::Address addr_);
	bool is_valid_sram_address(VIR::Address addr_);
	int get_sram_agu_init_delay_min(VIR::Coordinate reg_coord_, VIR::Coordinate sram_coord_);
	int get_sram_agu_middle_delay();
	int get_sram_agu_repetition_delay();
	int get_refi_agu_init_delay_min();
	int get_refi_agu_middle_delay();
	int get_refi_agu_repetition_delay();
	int get_sram_refi_distance(VIR::Coordinate reg_coord_, VIR::Coordinate sram_coord_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_SRAM_ADDRESS_TRANSFORMER_HPP__