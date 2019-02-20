
#ifndef __IfStatement_h__
#define __IfStatement_h__

#include "ControlStatement.hpp"
#include "IfMode.hpp"
#include "Expression.hpp"
#include "DPUPragma.hpp"
#include <exception>
using namespace std;

namespace VIR
{
// class ControlStatement;
class IfStatement;
namespace VirEnumerations
{
// enum IfMode;
}
} // namespace VIR

namespace VIR
{
class IfStatement : public VIR::ControlStatement
{
private:
	VIR::Expression *_condition;

private:
	vector<Statement *> _thenPart;
	vector<Statement *> _elsePart;

private:
	VIR::VirEnumerations::IfMode _mode;

private:
	VIR::DPUPragma *_conditionPragma;

public:
	VIR::Expression *condition() const;

public:
	void condition(Expression *condition_);

public:
	vector<Statement *> &thenPart();
	vector<Statement *> &elsePart();

public:
	VIR::VirEnumerations::IfMode mode() const;

public:
	void mode(VIR::VirEnumerations::IfMode mode_);

public:
	VIR::DPUPragma *conditionPragma() const;

public:
	void conditionPragma(VIR::DPUPragma *conditionPragma_);
};
} // namespace VIR

#endif
