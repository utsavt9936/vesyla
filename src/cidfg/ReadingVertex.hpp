#ifndef __VESYLA_CIDFG_READING_VERTEX_HPP__
#define __VESYLA_CIDFG_READING_VERTEX_HPP__

#include "FunctionVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class ReadingVertex : public FunctionVertex
{
public:
	bool is_sram;

public:
	ReadingVertex();
	~ReadingVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_READING_VERTEX_HPP__