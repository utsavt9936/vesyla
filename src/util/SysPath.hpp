#ifndef __VESYLA_UTIL_SYS_PATH_HPP__
#define __VESYLA_UTIL_SYS_PATH_HPP__

#include "GlobalVar.hpp"
#include <boost/filesystem.hpp>
#include <string>

using namespace std;

namespace vesyla {
namespace util {

class SysPath {
public:
	SysPath();
	static string find_config_file(const string filename);

private:
	string curr_dir();
	string home_dir();
	string conf_dir();
	string temp_dir();
	string prog_dir();
};

}
}

#endif // __VESYLA_UTIL_SYS_PATH_HPP__
