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

#ifndef __VESYLA_CODE_GEN_PRIMITIVE_FUNC_LIB_HPP__
#define __VESYLA_CODE_GEN_PRIMITIVE_FUNC_LIB_HPP__

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <map>
#include "util/Common.hpp"

using namespace std;

namespace vesyla
{
namespace codegen
{

class PrimitiveFuncLib
{

public:
	struct FuncConfig
	{
		int mode;
		int exec_cycle;
		bool reductive;
		bool output_register;
		map<int, int> arg_port;
		map<int, int> ret_port;
	};

public:
	/**
	 * \brief Load XML formatted primitive function defination.
	 * \param path The path to file.
	 */
	void load(const string path);
	/**
	 * \brief Find the DPU mode of a function.
	 * \param name The name of the function.
	 * \return The DPU mode or -1 if the function is invalid.
	 */
	int get_mode(const string name) const;
	/**
	 * \brief Find the execution cycle of a function.
	 * \param name The name of the function.
	 * \return The execution cycle or -1 if the function is invalid.
	 * \warning The returned execution cycle is the real execution cycle minus 1.
	 * e.g, ADD function will consume 1 clock cycle, the returned execution cycle
	 * for ADD should be zero.
	 */
	int get_exec_cycle(const string name) const;
	/**
	 * \brief Check if the function is reductive function.
	 * \param name The name of the function.
	 * \return true if it is a reductive function, otherwise false.
	 */
	bool get_reductive(const string name) const;
	/**
	 * \brief Check if the output of the function is registered or not.
	 * \param name The name of the function.
	 * \return true if it is registered, otherwise false.
	 */
	bool get_output_register(const string name) const;
	/**
	 * \brief Find the input port position of a function.
	 * \param name The name of the function.
	 * \param arg_pos The index of the argument.
	 * \return The input port position or -1 if the function or argument position
	 *         is invalid.
	 */
	int get_in_port(const string name, const int arg_pos) const;
	/**
	 * \brief Find the output port position of a function.
	 * \param name The name of the function.
	 * \param ret_pos The index of the returned value.
	 * \return The output port position or -1 if the function or return position
	 *         is invalid.
	 */
	int get_out_port(const string name, const int ret_pos) const;

private:
	map<string, FuncConfig> _primitive_func_map;
};

} // namespace codegen
} // namespace vesyla
#endif // __VESYLA_CODE_GEN_PRIMITIVE_FUNC_LIB_HPP__
