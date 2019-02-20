#ifndef __VESYLA_CIDFG_INDEXING_VERTEX_HPP__
#define __VESYLA_CIDFG_INDEXING_VERTEX_HPP__

#include "FunctionVertex.hpp"
#include "ConstVertex.hpp"

namespace vesyla
{
namespace cidfg
{
class IndexingVertex : public FunctionVertex
{
public:
	IndexingVertex();
	~IndexingVertex();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_INDEXING_VERTEX_HPP__