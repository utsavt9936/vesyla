#ifndef __VESYLA_CIDFG_VAR_VERTEX_HPP__
#define __VESYLA_CIDFG_VAR_VERTEX_HPP__

#include "SourceVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class VarVertex : public SourceVertex
{
public:
	bool is_iterator;
	int loop_id;

public:
	VarVertex();
	~VarVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_VAR_VERTEX_HPP__