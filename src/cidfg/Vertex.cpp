#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
Vertex::Vertex()
{
}
Vertex::~Vertex()
{
}
bool Vertex::is_hierarchical()
{
	if (vertex_type == ROOT_VERTEX ||
			vertex_type == GENERAL_HIERARCHICAL_VERTEX ||
			vertex_type == BRANCH_VERTEX ||
			vertex_type == LOOP_VERTEX ||
			vertex_type == HIERARCHICAL_INSTR_VERTEX)
	{
		return true;
	}
	return false;
}
bool Vertex::is_instr()
{
	if (vertex_type == RACCU_INSTR_VERTEX ||
			vertex_type == DPU_INSTR_VERTEX ||
			vertex_type == SWB_INSTR_VERTEX ||
			vertex_type == REFI_INSTR_VERTEX ||
			vertex_type == LOOPH_INSTR_VERTEX ||
			vertex_type == LOOPT_INSTR_VERTEX ||
			vertex_type == BRANCH_INSTR_VERTEX ||
			vertex_type == JUMP_INSTR_VERTEX ||
			vertex_type == WAIT_INSTR_VERTEX ||
			vertex_type == ROUTE_INSTR_VERTEX ||
			vertex_type == SRAM_INSTR_VERTEX ||
			vertex_type == HIERARCHICAL_INSTR_VERTEX)
	{
		return true;
	}
	return false;
}

bool Vertex::is_source()
{
	if (vertex_type == VAR_VERTEX ||
			vertex_type == REG_VAR_VERTEX ||
			vertex_type == SRAM_VAR_VERTEX ||
			vertex_type == CONST_VERTEX)
	{
		return true;
	}
	return false;
}

bool Vertex::is_sink()
{
	if (vertex_type == REG_SINK_VERTEX ||
			vertex_type == SRAM_SINK_VERTEX ||
			vertex_type == VAR_SINK_VERTEX)
	{
		return true;
	}
	return false;
}

} // namespace cidfg
} // namespace vesyla