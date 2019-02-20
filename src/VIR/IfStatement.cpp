#include <exception>
using namespace std;

#include "IfStatement.hpp"
#include "ControlStatement.hpp"
#include "IfMode.hpp"

VIR::Expression *VIR::IfStatement::condition() const
{
	return _condition;
}

void VIR::IfStatement::condition(Expression *condition_)
{
	_condition = condition_;
}

vector<VIR::Statement *> &VIR::IfStatement::thenPart()
{
	return _thenPart;
}

vector<VIR::Statement *> &VIR::IfStatement::elsePart()
{
	return _elsePart;
}

VIR::VirEnumerations::IfMode VIR::IfStatement::mode() const
{
	return _mode;
}

void VIR::IfStatement::mode(VIR::VirEnumerations::IfMode mode_)
{
	_mode = mode_;
}

VIR::DPUPragma *VIR::IfStatement::conditionPragma() const
{
	return _conditionPragma;
}

void VIR::IfStatement::conditionPragma(VIR::DPUPragma *conditionPragma_)
{
	_conditionPragma = conditionPragma_;
}
