#ifndef __VESYLA_CODEGEN_RACCU_VAR_MANAGER_HPP__
#define __VESYLA_CODEGEN_RACCU_VAR_MANAGER_HPP__

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"

namespace vesyla
{
namespace codegen
{
class RaccuVarManager
{
private:
	int _reg_num;
	map<string, int> _curr_index;

public:
	RaccuVarManager(int reg_num_ = 8) : _reg_num(reg_num_)
	{
		_curr_index = {};
	}
	int push(VIR::Coordinate coord_);
	int pop(VIR::Coordinate coord_);
	int top(VIR::Coordinate coord_);
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_RACCU_VAR_MANAGER_HPP__