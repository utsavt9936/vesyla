#include "Config.hpp"

namespace vesyla
{
namespace util
{

Config::Config(string config_file_)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(config_file_, pt);
	GlobalVar glv;

	for (ptree::value_type &v : pt.get_child("config"))
	{
		if (v.first == "entry")
		{
			string name = v.second.get("<xmlattr>.name", "");
			string type = v.second.get("<xmlattr>.type", "");
			string value = v.second.get("<xmlattr>.value", "");
			if (type == "int")
			{
				glv.puti(name, stoi(value));
			}
			else if (type == "float")
			{
				glv.putf(name, stof(value));
			}
			else if (type == "bool")
			{
				glv.putb(name, stoi(value));
			}
			else
			{
				glv.puts(name, value);
			}
		}
	}
}

Config::~Config()
{
}

} // namespace util
} // namespace vesyla
