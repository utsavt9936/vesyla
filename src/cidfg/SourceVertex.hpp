#ifndef __VESYLA_CIDFG_SOURCE_VERTEX_HPP__
#define __VESYLA_CIDFG_SOURCE_VERTEX_HPP__

#include "Vertex.hpp"

namespace vesyla
{
namespace cidfg
{
class SourceVertex : public Vertex
{
public:
	enum ValueType
	{
		UNKNOWN,
		INT,
		FLOAT
	};

public:
	string var_name;

public:
	SourceVertex();
	virtual ~SourceVertex() = 0;
};

} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_SOURCE_VERTEX_HPP__