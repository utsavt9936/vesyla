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

#include "util/Common.hpp"
#include "Template.hpp"

namespace vesyla
{
namespace instr
{
class Argument
{
private:
	string _key;
	string _type;
	void *_p_value;

public:
	Argument(string key_ = "", string type_ = "", const void *p_value_ = nullptr);
	~Argument();
	string key();
	string type();
	bool get_bool_value();
	int get_int_value();
	float get_float_value();
	string get_string_value();
	bool set_bool_value(bool val_);
	bool set_int_value(int val_);
	bool set_float_value(float val_);
	bool set_string_value(const string val_);

	vector<bool> to_bin(int bitwidth_);
	string to_str();
};
class Instruction
{
private:
	string _name;
	vector<Argument> _args;
	unordered_map<string, int> _name2pos;
	Template _t;

public:
	Instruction(string name_, Template t_);
	~Instruction();

	bool get_bool_argument(string name_);
	int get_int_argument(string name_);
	float get_float_argument(string name_);
	string get_string_argument(string name_);
	bool set_bool_argument(string name_, bool val_);
	bool set_int_argument(string name_, int val_);
	bool set_float_argument(string name_, float val_);
	bool set_string_argument(string name_, const string val_);

	vector<bool> to_bin();
	string to_str();
};
} // namespace instr
} // namespace vesyla
