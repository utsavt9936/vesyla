#ifndef __VESYLA_CIDFG_WAIT_INSTR_VERTEX_HPP__
#define __VESYLA_CIDFG_WAIT_INSTR_VERTEX_HPP__

#include "InstrVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class WaitInstrVertex : public InstrVertex
{
public:
	WaitInstrVertex();
	~WaitInstrVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_WAIT_INSTR_VERTEX_HPP__