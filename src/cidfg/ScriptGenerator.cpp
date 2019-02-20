#include "ScriptGenerator.hpp"

namespace vesyla
{
namespace cidfg
{
ScriptGenerator::ScriptGenerator()
{
}
ScriptGenerator::~ScriptGenerator()
{
}
string ScriptGenerator::generate()
{
	string str = "";
	str += "#!/usr/bin/env bash\n";
	str += "\n";
	str += "for file in ./*.dot; do\n";
	str += "basename=${file\%.*}\n";
	str += "dot -Tpdf ${basename}.dot -o ${basename}.pdf\n";
	str += "done\n";
	return str;
}
} // namespace cidfg
} // namespace vesyla