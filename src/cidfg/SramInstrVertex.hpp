#ifndef __VESYLA_CIDFG_SRAM_INSTR_VERTEX_HPP__
#define __VESYLA_CIDFG_SRAM_INSTR_VERTEX_HPP__

#include "InstrVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class SramInstrVertex : public InstrVertex
{
public:
  VIR::Coordinate sram_coord;

public:
  SramInstrVertex();
  ~SramInstrVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_SRAM_INSTR_VERTEX_HPP__