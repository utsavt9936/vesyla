#ifndef __VESYLA_FILEGEN_FILE_GENERATOR_HPP__
#define __VESYLA_FILEGEN_FILE_GENERATOR_HPP__

#include "BIR/BIRIncludeAll.hpp"
#include "ManasGenenator.hpp"
#include "SramImageGenerator.hpp"
#include "MatlabGenerator.hpp"

using namespace BIR;

namespace vesyla
{
namespace filegen
{
class FileGenerator
{
private:
public:
	FileGenerator() {}
	~FileGenerator() {}
	/**
	 * This function generate all the files as the output of the compiler.
	 * It is a wrap function for all generators belongs to vesyla::filegen.
	 */
	void generate(DRRACluster *drra_cluster_);
};
} // namespace filegen
} // namespace vesyla

#endif // __VESYLA_FILEGEN_FILE_GENERATEOR_HPP__