#ifndef __VESYLA_VERIFY_COMPARATOR_HPP__
#define __VESYLA_VERIFY_COMPARATOR_HPP__

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

namespace vesyla{
namespace verify{

class Comparator{

public:
	Comparator(const string& path_matlab, const string& path_fabric);
	bool compare();
	
public:
	map<string, vector<float>> get_tokens(const string& path);

private:
	map<string, vector<float>> _matlab_tokens;
	map<string, vector<float>> _fabric_tokens;
};

}
}
#endif
