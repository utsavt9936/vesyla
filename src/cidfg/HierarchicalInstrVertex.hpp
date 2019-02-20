#ifndef __VESYLA_CIDFG_HIERARCHICAL_INSTR_VERTEX_HPP__
#define __VESYLA_CIDFG_HIERARCHICAL_INSTR_VERTEX_HPP__

#include "InstrVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class HierarchicalInstrVertex : public InstrVertex
{
public:
	string name;
	map<string, vector<vector<int>>> rot;
	bool is_bulk;

public:
	HierarchicalInstrVertex();
	~HierarchicalInstrVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_HIERARCHICAL_INSTR_VERTEX_HPP__