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

#include "Instruction.hpp"

namespace vesyla
{
namespace instr
{
Argument::Argument(string key_ = "", string type_ = "", const void *p_value_ = nullptr)
{
	_key = key_;
	_type = type_;
	if (p_value_ == nullptr)
	{
		_p_value = nullptr;
	}
	else
	{
		if (_type == "bool")
		{
			_p_value = (void *)(new bool);
			*((bool *)_p_value) = *((const bool *)p_value_);
		}
		else if (_type == "int")
		{
			_p_value = (void *)(new int);
			*((int *)_p_value) = *((const int *)p_value_);
		}
		else if (_type == "uint")
		{
			_p_value = (void *)(new int);
			*((unsigned int *)_p_value) = *((const unsigned int *)p_value_);
		}
		else if (_type == "fixed")
		{
			_p_value = (void *)(new float);
			*((float *)_p_value) = *((const float *)p_value_);
		}
		else if (_type == "ufloat")
		{
			_p_value = (void *)(new float);
			*((float *)_p_value) = *((const float *)p_value_);
		}
		else if (_type == "string")
		{
			_p_value = (void *)(new string);
			*((string *)_p_value) = *((const string *)p_value_);
		}
		else
		{
			_p_value = nullptr;
		}
	}
}
Argument::~Argument()
{
	if (_p_value != nullptr)
	{
		if (_type == "bool")
		{
			delete ((bool *)_p_value);
		}
		else if (_type == "int")
		{
			delete ((int *)_p_value);
		}
		else if (_type == "uint")
		{
			delete ((uint *)_p_value);
		}
		else if (_type == "fixed")
		{
			delete ((float *)_p_value);
		}
		else if (_type == "ufixed")
		{
			delete ((float *)_p_value);
		}
		else if (_type == "float")
		{
			delete ((float *)_p_value);
		}
		else if (_type == "string")
		{
			delete ((string *)_p_value);
		}
		else
		{
			LOG(FATAL) << "Unknown argument data type " << _type;
		}
	}
}
string Argument::key()
{
	return _key;
}
string Argument::type()
{
	return _type;
}
bool Argument::get_bool_value()
{
	CHECK_EQ(_type, "bool") << "Argument " << _key << "is not of type 'bool'";
	return *((bool *)_p_value);
}
int Argument::get_int_value()
{
	CHECK_EQ(_type, "int") << "Argument " << _key << "is not of type 'int'";
	return *((int *)_p_value);
}
unsigned int Argument::get_uint_value()
{
	CHECK_EQ(_type, "uint") << "Argument " << _key << "is not of type 'uint'";
	return *((int *)_p_value);
}
float Argument::get_fixed_value()
{
	CHECK_EQ(_type, "fixed") << "Argument " << _key << "is not of type 'fixed'";
	return *((float *)_p_value);
}
float Argument::get_ufixed_value()
{
	CHECK_EQ(_type, "ufixed") << "Argument " << _key << "is not of type 'ufixed'";
	return *((float *)_p_value);
}
float Argument::get_float_value()
{
	CHECK_EQ(_type, "float") << "Argument " << _key << "is not of type 'float'";
	return *((float *)_p_value);
}
string Argument::get_string_value()
{
	CHECK_EQ(_type, "string") << "Argument " << _key << "is not of type 'string'";
	return *((string *)_p_value);
}
bool Argument::set_bool_value(bool val_)
{
	CHECK_EQ(_type, "bool") << "Argument " << _key << "is not of type 'bool'";
	*((bool *)_p_value) = val_;
	return true;
}
bool Argument::set_int_value(int val_)
{
	CHECK_EQ(_type, "int") << "Argument " << _key << "is not of type 'int'";
	*((int *)_p_value) = val_;
	return true;
}
bool Argument::set_float_value(float val_)
{
	CHECK_EQ(_type, "float") << "Argument " << _key << "is not of type 'float'";
	*((float *)_p_value) = val_;
	return true;
}
bool Argument::set_string_value(const string val_)
{
	CHECK_EQ(_type, "string") << "Argument " << _key << "is not of type 'string'";
	*((string *)_p_value) = val_;
	return true;
}

vector<bool> Argument::to_bin(int bitwidth_, int fraction_)
{
	CHECK_GT(bitwidth_, 0) << "Bitwidth should bigger than zero!";
	vector<bool> v;
	v.resize(bitwidth_, false);
	if (_p_value == nullptr)
	{
		LOG(WARNING) << "Argument " << _key << "doesn't have a value!";
		return v;
	}

	if (_type == "bool")
	{
		CHECK_EQ(bitwidth_, 1) << "Bitwidth for boolean must be 1";
		v[0] = *((bool *)_p_value);
	}
	else if (_type == "int")
	{
		int value = *((int *)_p_value);
		CHECK_LT(value, +(1 << bitwidth_ - 1)) << "Value out of bound!";
		CHECK_GE(value, -(1 << bitwidth_ - 1)) << "Value out of bound!";
		for (auto i = 0; i < bitwidth_; i++)
		{
			v[i] = value & 1;
			value = value >> 1;
		}
	}
	else if (_type == "uint")
	{
		unsigned int value = *((unsigned int *)_p_value);
		CHECK_LT(value, 1 << bitwidth_) << "Value out of bound!";

		for (auto i = 0; i < bitwidth_; i++)
		{
			v[i] = value & 1;
			value = value >> 1;
		}
	}
	else if (_type == "fixed")
	{
		int value = int(*((float *)_p_value) * (1 << fraction_));
		CHECK_LT(value, +(1 << bitwidth_ - 1)) << "Value out of bound!";
		CHECK_GE(value, -(1 << bitwidth_ - 1)) << "Value out of bound!";
		for (auto i = 0; i < bitwidth_; i++)
		{
			v[i] = value & 1;
			value = value >> 1;
		}
	}
	else if (_type == "ufixed")
	{
		unsigned int value = (unsigned int)(*((float *)_p_value) * (1 << fraction_));
		CHECK_LT(value, 1 << bitwidth_) << "Value out of bound!";

		for (auto i = 0; i < bitwidth_; i++)
		{
			v[i] = value & 1;
			value = value >> 1;
		}
	}
	else if (_type == "float")
	{
		CHECK_EQ(bitwidth_, 0) << "Bitwidth should be 32!";
		float value = *((float *)_p_value);

		for (auto i = 0; i < bitwidth_; i++)
		{
			v[i] = value & 1;
			value = value >> 1;
		}
	}
	else if (_type == "string")
	{
		delete ((bool *)_p_value);
	}
	else
	{
		LOG(FATAL) << "Unknown argument data type " << _type;
	}

	return v;
}

string to_str();

} // namespace instr
} // namespace vesyla