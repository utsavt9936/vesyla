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

#include "PrimitiveFuncLib.hpp"

namespace vesyla
{
namespace codegen
{

void PrimitiveFuncLib::load(const string path)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(path, pt);

	for (ptree::value_type &v : pt.get_child("PrimitiveFunctions"))
	{
		if (v.first == "func")
		{
			string func_name = v.second.get<string>("<xmlattr>.name", "");
			FuncConfig fc;
			fc.mode = v.second.get<int>("<xmlattr>.mode", -1);
			fc.exec_cycle = v.second.get<int>("<xmlattr>.exec_cycle", -1);
			fc.reductive = v.second.get<bool>("<xmlattr>.reductive", false);
			fc.output_register = v.second.get<bool>("<xmlattr>.output_register", true);
			for (ptree::value_type &v1 : v.second.get_child(""))
			{
				if (v1.first == "in_port")
				{
					int arg_pos = v1.second.get<int>("<xmlattr>.arg_pos", -1);
					int port_pos = v1.second.get<int>("<xmlattr>.port_pos", -1);
					fc.arg_port[arg_pos] = port_pos;
				}
				else if (v1.first == "out_port")
				{
					int ret_pos = v1.second.get<int>("<xmlattr>.ret_pos", -1);
					int port_pos = v1.second.get<int>("<xmlattr>.port_pos", -1);
					fc.ret_port[ret_pos] = port_pos;
				}
			}
			_primitive_func_map[func_name] = fc;
		}
	}
}

int PrimitiveFuncLib::get_mode(const string func) const
{
	auto it = _primitive_func_map.find(func);
	if (it == _primitive_func_map.end())
	{
		LOG(WARNING) << "No such primitive function '" << func << "'!";
		return -1;
	}
	return it->second.mode;
}

int PrimitiveFuncLib::get_exec_cycle(const string func) const
{
	auto it = _primitive_func_map.find(func);
	if (it == _primitive_func_map.end())
	{
		LOG(WARNING) << "No such primitive function '" << func << "'!";
		return -1;
	}
	return it->second.exec_cycle;
}

bool PrimitiveFuncLib::get_reductive(const string func) const
{
	auto it = _primitive_func_map.find(func);
	if (it == _primitive_func_map.end())
	{
		LOG(WARNING) << "No such primitive function '" << func << "'!";
		return false;
	}
	return it->second.reductive;
}

bool PrimitiveFuncLib::get_output_register(const string func) const
{
	auto it = _primitive_func_map.find(func);
	if (it == _primitive_func_map.end())
	{
		LOG(WARNING) << "No such primitive function '" << func << "'!";
		return false;
	}
	return it->second.output_register;
}

int PrimitiveFuncLib::get_in_port(const string func, int arg_pos) const
{
	auto it = _primitive_func_map.find(func);
	if (it == _primitive_func_map.end())
	{
		LOG(WARNING) << "No such primitive function '" << func << "'!";
		return -1;
	}

	if (arg_pos < 0)
	{
		return -1;
	}

	auto itx = it->second.arg_port.find(arg_pos);
	if (itx == it->second.arg_port.end())
	{
		return -1;
	}

	return itx->second;
}

int PrimitiveFuncLib::get_out_port(const string func, int ret_pos) const
{
	auto it = _primitive_func_map.find(func);
	if (it == _primitive_func_map.end())
	{
		LOG(WARNING) << "No such primitive function '" << func << "'!";
		return -1;
	}

	if (ret_pos < 0)
	{
		return -1;
	}

	auto itx = it->second.ret_port.find(ret_pos);
	if (itx == it->second.ret_port.end())
	{
		return -1;
	}

	return itx->second;
}

} // namespace codegen
} // namespace vesyla
