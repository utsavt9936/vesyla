#ifndef __VESYLA_INSTR_DPU_INSTR_HPP__
#define __VESYLA_INSTR_DPU_INSTR_HPP__

#include "util/Common.hpp"
#include "BaseInstr.hpp"

namespace vesyla
{
namespace instr
{
class DpuInstr : BaseInstr
{
public:
  int dpu_mode;
  int dpu_saturation;
  int dpu_acc_clear_rst;
  int dpu_acc_clear_sd;
  int dpu_acc_clear;
  int dpu_process_inout;

public:
  DpuInstr();
  ~DpuInstr();

  string to_str();
  string to_bin_str();
  uint32_t to_bin();
};
} // namespace instr
} // namespace vesyla

#endif // __VESYLA_INSTR_DPU_INSTR_HPP__