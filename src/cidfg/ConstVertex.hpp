#ifndef __VESYLA_CIDFG_CONST_VERTEX_HPP__
#define __VESYLA_CIDFG_CONST_VERTEX_HPP__

#include "SourceVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class ConstVertex : public SourceVertex
{
public:
	ValueType value_type;
	int int_data;
	float float_data;

public:
	ConstVertex();
	~ConstVertex();
	void set_int_value(int v_);
	void set_float_value(float v_);
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_CONST_VERTEX_HPP__