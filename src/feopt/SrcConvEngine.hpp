#ifndef __VESYLA_FEOPT_SRC_CONV_ENGINE_HPP__
#define __VESYLA_FEOPT_SRC_CONV_ENGINE_HPP__

#include "Engine.hpp"

namespace vesyla
{
namespace feopt
{
/**
 * This class convert the variable declaration to source vertices.
 * Variable decleared as Register file vector or SRAM vector will be converted to
 * corresponding source vertices.
 * 
 * Declearation can be done by several ways.
 *  1) directly listing the elements;
 *  2) using zeros() or ones() function;
 *  3) using fi() to specify fixed number;
 */
class SrcConvEngine : Engine
{
public:
	void transform(cidfg::CidfgGraph &g_);

private:
};
} // namespace feopt
} // namespace vesyla

#endif // __VESYLA_FEOPT_SRC_CONV_ENGINE_HPP__