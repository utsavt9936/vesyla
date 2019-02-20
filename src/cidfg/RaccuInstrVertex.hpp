#ifndef __VESYLA_CIDFG_RACCU_INSTR_VERTEX_HPP__
#define __VESYLA_CIDFG_RACCU_INSTR_VERTEX_HPP__

#include "InstrVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class RaccuInstrVertex : public InstrVertex
{
	enum OperandType
	{
		RACCU_OPERAND_IMMEDIATE,
		RACCU_OPERAND_REGISTER
	};

public:
	OperandType op0_type;
	int op0_value;
	OperandType op1_type;
	int op1_value;
	int ret_value;
	string func_name;

public:
	RaccuInstrVertex();
	~RaccuInstrVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_RACCU_INSTR_VERTEX_HPP__