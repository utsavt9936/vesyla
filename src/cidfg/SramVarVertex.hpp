#ifndef __VESYLA_CIDFG_SRAM_VAR_VERTEX_HPP__
#define __VESYLA_CIDFG_SRAM_VAR_VERTEX_HPP__

#include "SourceVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class SramVarVertex : public SourceVertex
{
public:
	ValueType value_type;
	vector<int> int_data_array;
	vector<float> float_data_array;
	VIR::Coordinate sram_coord;

public:
	SramVarVertex();
	SramVarVertex(VIR::AssignmentStatement *stmt_);
	~SramVarVertex();
	string dump();

private:
	vector<int> convert_to_int_array(VIR::Expression *e_);
	vector<float> convert_to_float_array(VIR::Expression *e_);
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_SRAM_VAR_VERTEX_HPP__