#include "Common.hpp"

namespace vesyla
{
namespace filegen
{
void Common::write_line(ofstream &ofs_, string s_, int intentation_level_, string intentation_)
{
	string str;
	for (int i = 0; i < intentation_level_; i++)
	{
		str += intentation_;
	}
	ofs_ << str << s_ << endl;
}
} // namespace filegen
} // namespace vesyla