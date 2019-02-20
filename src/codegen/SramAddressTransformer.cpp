#include "SramAddressTransformer.hpp"

namespace vesyla
{
namespace codegen
{
VIR::Address SramAddressTransformer::transform(VIR::Address addr_)
{
	return addr_;
	LOG(DEBUG) << addr_.n0.b();
	// If addr_ is already 2D and the Level 0 loop is 16 elements.
	if (addr_.n0.is_constant() == true && addr_.n0.b() == _width)
	{
		return addr_;
	}
	// If addr_ is 1D
	if (addr_.n1.is_constant() == true && addr_.n1.b() == 0)
	{
		VIR::Address new_addr;
		new_addr = addr_;
		new_addr.n1 = addr_.n0;
		new_addr.n1.div(_width);
		new_addr.n0.b(_width);
		new_addr.a1.multiply(_width);
		return new_addr;
	}

	LOG(FATAL) << "Illegal address pattern for DiMarch!";
}

bool SramAddressTransformer::is_valid_sram_address(VIR::Address addr_)
{
	if (addr_.n0.is_constant() == true && addr_.n0.b() == _width)
	{
		return true;
	}
	return false;
}

int SramAddressTransformer::get_sram_agu_init_delay_min(VIR::Coordinate reg_coord_, VIR::Coordinate sram_coord_)
{
	// return the minimal cycle which is needed to allow the configuration travel
	// from SEQ to the destination DiMarch cell.
	//
	// The distance is calculated by equation:
	// D = # of hops

	int hop = abs(reg_coord_.row - sram_coord_.row) + abs(reg_coord_.column - sram_coord_.column);
	return hop;
}

int SramAddressTransformer::get_sram_agu_middle_delay()
{
	// always return 0, because the L1 address is handled internally by DiMarch AGU
	// It always spend _width/_agu_num cycles to assemble a _width word block then
	// send to Register file.
	return 0;
}

int SramAddressTransformer::get_sram_agu_repetition_delay()
{
	// always return 0, because the L2 address is handled internally by DiMarch AGU
	// It always immediately assemble the second data block once the first one is
	// finished
	return 0;
}

int SramAddressTransformer::get_refi_agu_init_delay_min()
{
	return 0;
}

int SramAddressTransformer::get_refi_agu_middle_delay()
{
	// Level 1 loop is not used in order to have the exact behaviour of SRAM agu.
	return 0;
}

int SramAddressTransformer::get_refi_agu_repetition_delay()
{
	// every _width cycle, there should be a data block appearing on the bus.
	return _width / _agu_num;
}

int SramAddressTransformer::get_sram_refi_distance(VIR::Coordinate reg_coord_, VIR::Coordinate sram_coord_)
{
	int hop = abs(reg_coord_.row - sram_coord_.row) + abs(reg_coord_.column - sram_coord_.column);
	return hop;
}

} // namespace codegen
} // namespace vesyla