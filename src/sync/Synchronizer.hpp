#ifndef __VESYLA_SYNC_SYNCHRONIZER_HPP__
#define __VESYLA_SYNC_SYNCHRONIZER_HPP__

#include "../BIR/BIRIncludeAll.hpp"
#include "../VIR/VIRIncludeAll.hpp"
#include "../VManager/MemoryManager.hpp"
#include "../util/Common.hpp"

using namespace BIR;
using namespace BIR::BIREnumerations;
using namespace VIR;
using namespace VIR::VirEnumerations;

namespace vesyla
{
namespace sync
{

class Synchronizer
{
private:
  int _max_init_delay;
  int _max_middle_delay;
  int _max_repetition_number;
  int _max_repetition_offset;

private:
  vector<BIR::Instruction *> sync_one_cell(vector<BIR::Instruction *> instr_list_, int end_time_);
  void add_wait(vector<BIR::Instruction *> &instr_list_, int &pc_,
                int &clk_, int num_cycles_);
  void sync_instr(vector<BIR::Instruction *> &instr_list_, int &pc, int &clk, Instruction *instr);
  vector<BIR::Instruction *> adjust_refis(vector<BIR::Instruction *> instr_list_);

public:
  Synchronizer(int max_init_delay_ = 15, int max_middle_delay_ = 64, int max_repetition_number_ = 8, int max_repetition_offset_ = 16) : _max_init_delay(max_init_delay_), _max_middle_delay(max_middle_delay_), _max_repetition_number(max_repetition_number_), _max_repetition_offset(max_repetition_offset_)
  {
  }
  ~Synchronizer()
  {
  }
  map<string, vector<BIR::Instruction *>> synchronize(map<string, vector<BIR::Instruction *>> instr_lists_, int end_time_);
};

} // namespace sync
} // namespace vesyla

#endif // __VESYLA_SYNC_SYNCHRONIZER_HPP__