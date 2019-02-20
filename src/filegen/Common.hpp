#ifndef __VESYLA_FILEGEN_COMMON_HPP__
#define __VESYLA_FILEGEN_COMMON_HPP__

#include "util/Common.hpp"

namespace vesyla
{
namespace filegen
{
class Common
{
public:
	static void write_line(ofstream &ofs_, string s_, int indentation_level_ = 0, string intentation_ = "\t");
};
} // namespace filegen
} // namespace vesyla
#endif // __VESYLA_FILEGEN_COMMON_HPP__