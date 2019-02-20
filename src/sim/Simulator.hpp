#ifndef __VESYLA_SIM_SIMULATOR_HPP__
#define __VESYLA_SIM_SIMULATOR_HPP__

#include "Model.hpp"

namespace vesyla
{
namespace sim
{
class Simulator
{
public:
	int simulate(map<string, vector<BIR::Instruction *>> instr_list_);
};
} // namespace sim
} // namespace vesyla

#endif // __VESYLA_SIM_SIMULATOR_HPP__