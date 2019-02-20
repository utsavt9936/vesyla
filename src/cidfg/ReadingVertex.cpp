#include "ReadingVertex.hpp"

namespace vesyla
{
namespace cidfg
{
ReadingVertex::ReadingVertex()
{
	vertex_type = READING_VERTEX;
	is_sram = false;
}
ReadingVertex::~ReadingVertex()
{
}
} // namespace cidfg
} // namespace vesyla