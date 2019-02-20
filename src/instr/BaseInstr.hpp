#ifndef __VESYLA_INSTR_BASE_INSTR_HPP__
#define __VESYLA_INSTR_BASE_INSTR_HPP__

#include "util/Common.hpp"

namespace vesyla
{
namespace instr
{
/*!
 * The base class of Manas instruction
 */
class BaseInstr
{
public:
  enum InstrType
  {
    DPU_INSTR,
    REFI_INSTR,
    REFI1_INSTR,
    REFI2_INSTR,
    REFI3_INSTR,
    SWB_INSTR,
    ROUTE_INSTR,
    SRAM_INSTR,
    WAIT_INSTR,
    LOOPH_INSTR,
    LOOPT_INSTR,
    BRANCH_INSTR,
    JUMP_INSTR,
    RACCU_INSTR,
    HALT_INSTR
  };

public:
  //! The unique id.
  int id;
  //! The instruction type, defined in constructor of each derived class.
  int type;
  //! The labels that link this instruction to the vertices in dependency graph.
  vector<string> labels;

public:
  BaseInstr();
  virtual ~BaseInstr() = 0;

  //! Generate verbo format instruction, used in VHDL generation.
  virtual string to_str() = 0;
  //! Generate binary representation as string
  virtual string to_bin_str() = 0;
  //! Generate binary representation as integer
  virtual uint32_t to_bin() = 0;
};
} // namespace instr
} // namespace vesyla

#endif // __VESYLA_INSTR_BASE_INSTR_HPP__