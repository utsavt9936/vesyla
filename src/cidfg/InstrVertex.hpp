#ifndef __VESYLA_CIDFG_INSTR_VERTEX_HPP__
#define __VESYLA_CIDFG_INSTR_VERTEX_HPP__

#include "HierarchicalVertex.hpp"
#include "BIR/BIRIncludeAll.hpp"

namespace vesyla
{
namespace cidfg
{
class InstrVertex : public HierarchicalVertex
{
public:
	BIR::Instruction *instr;

public:
	InstrVertex();
	~InstrVertex() = 0;
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_INSTR_VERTEX_HPP__