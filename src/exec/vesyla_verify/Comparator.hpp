// Copyright (C) 2019 Yu Yang
//
// This file is part of Vesyla.
//
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

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

namespace vesyla
{
namespace verify
{

class Comparator
{

public:
	Comparator(const string &path_matlab, const string &path_fabric);
	bool compare();

public:
	map<string, vector<float>> get_tokens(const string &path);

private:
	map<string, vector<float>> _matlab_tokens;
	map<string, vector<float>> _fabric_tokens;
};

} // namespace verify
} // namespace vesyla
#endif
