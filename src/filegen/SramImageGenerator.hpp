#ifndef __VESYLA_FILEGEN_SRAM_IMAGE_GENERATOR_HPP__
#define __VESYLA_FILEGEN_SRAM_IMAGE_GENERATOR_HPP__

#include <boost/algorithm/string.hpp>
#include "util/Common.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "Common.hpp"

using namespace BIR;
using namespace BIR::BIREnumerations;
namespace vesyla
{
namespace filegen
{
class SramImageGenerator
{
private:
public:
	SramImageGenerator() {}
	~SramImageGenerator() {}
	void generate(map<string, SRAM *> sram_lists_, string filename_);
};
} // namespace filegen
} // namespace vesyla

#endif // __VESYLA_FILEGEN_SRAM_IMAGE_GENERATOR_HPP__