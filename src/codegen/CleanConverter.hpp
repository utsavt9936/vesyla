#ifndef __VESYLA_CODEGEN_CLEAN_CONVERTER_HPP__
#define __VESYLA_CODEGEN_CLEAN_CONVERTER_HPP__

#include "cidfg/CidfgGraph.hpp"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/sequential_vertex_coloring.hpp>
#include <cidfg/VarTable.hpp>
#include "BIR/BIRIncludeAll.hpp"
#include "VManager/MemoryManager.hpp"

namespace vesyla
{
namespace codegen
{
class CleanConverter
{
public:
	CleanConverter();
	~CleanConverter();

public:
	void convert(cidfg::CidfgGraph &g_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_CLEAN_CONVERTER_HPP__