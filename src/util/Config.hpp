#ifndef __VESYLA_UTIL_CONFIG_HPP__
#define __VESYLA_UTIL_CONFIG_HPP__

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "GlobalVar.hpp"

using namespace std;

namespace vesyla
{
namespace util
{
class Config
{
public:
	Config(string config_file_);
	~Config();
};

} // namespace util
} // namespace vesyla

#endif // __VESYLA_UTIL_CONFIG_HPP__
