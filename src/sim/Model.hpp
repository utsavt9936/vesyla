#ifndef __VESYLA_SIM_MODEL_HPP__
#define __VESYLA_SIM_MODEL_HPP__

#include "util/Common.hpp"
#include "BIR/BIRIncludeAll.hpp"

namespace vesyla
{
namespace sim
{
class Model
{
public:
	struct LoopManager
	{
		int iterator;
		bool is_active;
		bool is_last_iteration;

		LoopManager() : iterator(0), is_active(false), is_last_iteration(false) {}
	};

private:
	vector<int> _raccu_regs;
	vector<LoopManager> _loop_managers;
	int _pc;
	int _clk;
	stack<int> _stack;

public:
	Model(int raccu_reg_count_ = 8, int loop_manager_count_ = 4);
	~Model();
	int simulate(vector<BIR::Instruction *> instrs_);
	void reset();
};
} // namespace sim
} // namespace vesyla

#endif // __VESYLA_SIM_MODEL_HPP__