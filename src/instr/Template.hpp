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

namespace vesyla
{
namespace instr
{
class ArgumentTemplate
{
public:
	string arg_name;
	string arg_type;
	string arg_default;
	int arg_bitwidth;
	int arg_position;
};

class InstructionTemplate
{
public:
	string instr_name;
	int instr_code;
	int instr_code_bitwidth;
	unordered_map<string, ArgumentTemplate> instr_args;
};

class Template
{
public:
	unordered_map<string, InstructionTemplate> table;

public:
	Template();
	Template(string path_);
	bool load_from_xml(string path_);
};
} // namespace instr
} // namespace vesyla