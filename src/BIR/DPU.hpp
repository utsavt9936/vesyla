#include <exception>
using namespace std;

#ifndef __DPU_h__
#define __DPU_h__

#include "BIRBase.hpp"
#include "DPUMode.hpp"
#include "DPUInstruction.hpp"

namespace BIR
{
// class BIRBase;
class DPU;
namespace BIREnumerations
{
// enum DPUMode;
}
} // namespace BIR

namespace BIR
{
class DPU : public BIR::BIRBase
{
private:
	BIR::BIREnumerations::DPUMode _mode;

private:
	int _clkCounter;

private:
	BIR::DPUInstruction *_prevDpuInstruction;

private:
	int _operandNum;

public:
	DPU();

public:
	BIR::BIREnumerations::DPUMode mode() const;

public:
	void mode(BIR::BIREnumerations::DPUMode mode_);

public:
	int clkCounter() const;

public:
	void clkCounter(int clkCounter_);

public:
	BIR::DPUInstruction *prevDpuInstruction() const;

public:
	void prevDpuInstruction(BIR::DPUInstruction *prevDpuInstruction_);

public:
	int operandNum() const;
};
} // namespace BIR

#endif
