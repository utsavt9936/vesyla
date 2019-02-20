#include "RaccuInstrVertex.hpp"

namespace vesyla
{
namespace cidfg
{
RaccuInstrVertex::RaccuInstrVertex()
{
	vertex_type = RACCU_INSTR_VERTEX;
	op0_type = RACCU_OPERAND_IMMEDIATE;
	op1_type = RACCU_OPERAND_IMMEDIATE;
	op0_value = 0;
	op1_value = 1;
	func_name = "silago_raccu_undefined";
}
RaccuInstrVertex::~RaccuInstrVertex()
{
}
} // namespace cidfg
} // namespace vesyla