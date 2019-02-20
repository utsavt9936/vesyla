#include "Simulator.hpp"

namespace vesyla
{
namespace sim
{
int Simulator::simulate(map<string, vector<BIR::Instruction *>> instr_list_)
{
	int max_time = 0;
	for (auto &p : instr_list_)
	{
		Model m;
		int t = m.simulate(p.second);
		if (t > max_time)
		{
			max_time = t;
		}
	}
	util::GlobalVar glv;
	glv.puti("max_exec_time", max_time);
	return max_time;
}
} // namespace sim
} // namespace vesyla